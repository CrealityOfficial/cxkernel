#include "nest2djobex.h"
#include "qtusercore/module/progressortracer.h"

#if USE_NESTPLACER
#include "nestplacer/nestplacer.h"
#endif

#include "nestplacer/placer.h"
#include "cxkernel/interface/constinterface.h"
#include "cxkernel/interface/cacheinterface.h"
#include "placeitem.h"

using namespace nestplacer;

namespace cxkernel
{
    Nest2DJobEx::Nest2DJobEx(QObject* parent)
        : Job(parent)
        , m_modelspacing(1.0f)
        , m_platformSpacing(1.0f)
        , m_angle(45)
        , m_panDistance(10.0f)
    {
    }

    Nest2DJobEx::~Nest2DJobEx()
    {

    }

    void Nest2DJobEx::setBounding(const trimesh::box3& box)
    {
        m_box = box;
    }

    void Nest2DJobEx::setPanDistance(float distance)
    {
        m_panDistance = distance;
    }
	
	void Nest2DJobEx::setLayoutParameter(const float& modelSpacing, const float& platformSpacing, const int& angle, const bool alignMove)
	{
		m_modelspacing = modelSpacing;
		m_platformSpacing = platformSpacing;
		m_angle = angle;
		m_alignMove = alignMove;
	}

    QString Nest2DJobEx::name()
    {
        return "qcxutil::Nest2DJobEx";
    }

    QString Nest2DJobEx::description()
    {
        return "qcxutil::Nest2DJobEx";
    }

    void Nest2DJobEx::failed()
    {
    }

    bool caseInsensitiveLessThan(PlaceItemEx* item1, PlaceItemEx* item2)
    {
        //trimesh::box3 b1 = item1->globalBox();
        //trimesh::box3 b2 = item2->globalBox();
        //return  b1.size().z > b2.size().z;
        return false;
    }

    // invoke from main thread
    void Nest2DJobEx::successed(qtuser_core::Progressor* progressor)
    {
    }

    void Nest2DJobEx::work(qtuser_core::Progressor* progressor)
    {
        beforeWork();

        qtuser_core::ProgressorTracer tracer(progressor);

        doLayout(tracer);

        afterWork();
    }

    void Nest2DJobEx::beforeWork()
    {
    }

    void Nest2DJobEx::afterWork()
    {
    }

    void Nest2DJobEx::doLayout(ccglobal::Tracer& tracer)
    {
        YDefaultBinExtendStrategy binExtendStrategy(m_box, m_panDistance);

        PlacerParameter parameter;
		parameter.itemGap = m_modelspacing;
		parameter.binItemGap = m_platformSpacing;
		parameter.rotate = (m_angle ==0 ? false : true);
		parameter.rotateAngle = m_angle;
		parameter.needAlign = m_alignMove;
		
        if (!cxkernel::isReleaseVersion())
        {
            QString cacheName = cxkernel::createNewAlgCache("autolayout");
			parameter.fileName = cacheName.toLocal8Bit().constData();
        }

        std::vector<nestplacer::PlacerItem*> fixed;
        std::vector<nestplacer::PlacerItem*> actives;
        std::vector<PlacerResultRT> results;

        for (int i = 0; i < m_fixedOutlines.size(); i++)
        {
            fixed.push_back(new PlaceItemEx(m_fixedOutlines[i]));
        }

        for (int k = 0; k < m_activeOutlines.size(); k++)
        {
            actives.push_back(new PlaceItemEx(m_activeOutlines[k]));
        }

        place(fixed, actives, parameter, results, binExtendStrategy);

        const float EPSINON = 0.00001f;
        for (int i = 0; i < results.size(); i++)
        {
            if (results[i].rt.x >= -EPSINON && results[i].rt.x <= EPSINON
                && results[i].rt.y >= -EPSINON && results[i].rt.y <= EPSINON)
            {
                continue;
            }

            NestResultEx aResult;
            aResult.binIndex = results[i].binIndex;
            aResult.rt = results[i].rt;
            m_results.push_back(aResult);
        }

        for (int i = 0; i < fixed.size(); i++)
        {
            if (fixed[i])
            {
                delete fixed[i];
                fixed[i] = nullptr;
            }
        }

        for (int j = 0; j < actives.size(); j++)
        {
            if (actives[j])
            {
                delete actives[j];
                actives[j] = nullptr;
            }
        }

    }
}