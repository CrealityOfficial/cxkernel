#include "nest2djob.h"
#include "interface/spaceinterface.h"
#include "interface/visualsceneinterface.h"
#include "interface/modelinterface.h"
#include "interface/machineinterface.h"
#include "utils/modelpositioninitializer.h"

#include "qcxutil/trimesh2/conv.h"
#include "polygonLib/polygonLib.h"

namespace creative_kernel
{
    Nest2DJob::Nest2DJob(QObject* parent)
        : Job(parent)
        , m_insert(nullptr)
        , m_nestType(nestplacer::PlaceType::CENTER_TO_SIDE)
    {

    }

    Nest2DJob::~Nest2DJob()
    {

    }

    void Nest2DJob::setNestType(nestplacer::PlaceType type)
    {
        m_nestType = type;
    }

    void Nest2DJob::setInsertModelN(ModelN* model)
    {
        m_insert = model;
    }

    QString Nest2DJob::name()
    {
        return "Layout Calculate";
    }

    QString Nest2DJob::description()
    {
        return "";
    }

    void Nest2DJob::failed()
    {
        if (m_insert)
            m_insert->setParent(this);
    }

    bool caseInsensitiveLessThan(ModelN* s1, ModelN* s2)
    {
        qtuser_3d::Box3D s1box = s1->globalSpaceBox();
        qtuser_3d::Box3D s2box = s2->globalSpaceBox();
        return  s1box.size().z() > s2box.size().z();
    }

    std::vector<trimesh::vec3> outLine(ModelN* model)
    {
        QVector3D offset = model->localPosition();
        trimesh::vec3 toffset = trimesh::vec3(offset.x(), offset.y(), offset.z());
        std::vector<trimesh::vec3> lines;
        model->convex(lines);
        for (trimesh::vec3& v : lines)
            v -= toffset;
        return lines;
    }

    std::vector<trimesh::vec3> outLine_concave(ModelN* model)
    {
        QVector3D localPosition = model->localPosition();
        QMatrix4x4 globalMatrix = model->globalMatrix();
        QVector3D scalse = model->localScale();

        std::vector<trimesh::vec3> lines;
        std::vector<polygonLib::PointF> concaveHull;
        for (trimesh::point pt : model->mesh()->vertices)
        {
            QVector3D pt_rot = globalMatrix * QVector3D(pt.x, pt.y, pt.z);
            concaveHull.push_back(polygonLib::PointF(pt_rot.x(), pt_rot.y()));
        }
        concaveHull = polygonLib::PolygonPro::polygonConcaveHull(concaveHull, 0.2);

        for (polygonLib::PointF& v : concaveHull)
        {
            lines.push_back(trimesh::vec3((v.x - localPosition.x()) * scalse.x(), (v.y - localPosition.y()) * scalse.y(), 0));
        }
        return lines;
    }

    // invoke from main thread
    void Nest2DJob::successed(qtuser_core::Progressor* progressor)
    {
        QList<QVector3D> d_ts;
        QList<QQuaternion> d_qs;

        QList<QVector3D> s_ts;
        QList<QQuaternion> s_qs;

        QList<ModelN*> models;
        for (NestResult& result : m_result)
        {
            ModelN* m = result.model;
            QVector3D lt = m->localPosition();
            QQuaternion q = m->localQuaternion();

            models.push_back(m);

            QVector3D t = QVector3D(result.trans.x / NEST_FACTOR, result.trans.y / NEST_FACTOR, lt.z());

            QQuaternion dq = QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), result.trans.rotation);
            QQuaternion rq = dq * q;

            d_ts.push_back(t);
            d_qs.push_back(rq);

            s_ts.push_back(lt);
            s_qs.push_back(q);
        }

        mixTRModels(models, s_ts, d_ts, s_qs, d_qs, true);

        if (m_insert)
        {
            if (!currentMachineIsBelt())
            {
                if (!ModelPositionInitializer::nestLayout(m_insert))
                {
                    ModelPositionInitializer::layout(m_insert, progressor, false);
                }
            }
            else
            {
                ModelPositionInitializer::layoutBelt(m_insert, progressor, false);
            }

            bottomModel(m_insert);
            addModel(m_insert, true);
        }
    }

    void Nest2DJob::work(qtuser_core::Progressor* progressor)
    {
        m_models = modelns();
        m_size = qcxutil::qVector3D2Vec3(baseBoundingBox().size());
        std::sort(m_models.begin(), m_models.end(), caseInsensitiveLessThan);

        if (m_insert)
            insert();
        else
        {
            layoutAll();
        }
    }

    void Nest2DJob::insert()
    {
    }

    void Nest2DJob::layoutAll()
    {
        if (m_models.size() == 0)
            return;

        std::vector<int> modelIndices;
        for (int i = 0; i < m_models.size(); i++)
        {
            modelIndices.push_back(i);
        }
        trimesh::box3 workspaceBox(trimesh::vec3(0, 0, 0), m_size);
        std::vector < std::vector<trimesh::vec3>> modelsData;
        for (int m = 0; m < m_models.size(); m++)
        {
            std::vector<trimesh::vec3> oItem;
            if (nestplacer::PlaceType(m_nestType) == nestplacer::PlaceType::CONCAVE || 
                nestplacer::PlaceType(m_nestType) == nestplacer::PlaceType::CONCAVE_ALL)
                oItem = outLine_concave(m_models.at(m));
            else
                oItem = outLine(m_models.at(m));
            modelsData.push_back(oItem);
        }

        std::function<void(int, trimesh::vec3)> modelPositionUpdateFunc_nest = [this](int modelIndex, trimesh::vec3 newBoxCenter) {
            nestplacer::TransMatrix matrix;
            matrix.x = newBoxCenter.x * NEST_FACTOR;
            matrix.y = newBoxCenter.y * NEST_FACTOR;
            matrix.rotation = newBoxCenter.z;
            m_result.push_back(NestResult({ m_models[modelIndex], matrix }));
        };
        nestplacer::NestParaFloat para = nestplacer::NestParaFloat(workspaceBox, 10.0f, nestplacer::PlaceType(m_nestType), true);

        nestplacer::NestPlacer::layout_all_nest(modelsData, modelIndices, para, modelPositionUpdateFunc_nest);
    }
}