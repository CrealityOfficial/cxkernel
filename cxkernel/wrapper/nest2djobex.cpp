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
        , m_insert(nullptr)
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

    void Nest2DJobEx::setInsertItemOutline(const std::vector<trimesh::vec3>& insertItemOutline)
    {
        m_insert = new PlaceItemEx(insertItemOutline, this);
    }

    void Nest2DJobEx::setPlaceItems(const std::vector<PlaceItemEx*>& fixedItems, const std::vector<PlaceItemEx*>& activeItems)
    {
        m_fixedItems = fixedItems;
        m_activeItems = activeItems;
    }
	void Nest2DJobEx::setLayoutParameter(const float& modelSpacing, const float& platformSpacing, const int& angle)
	{
		m_modelspacing = modelSpacing;
		m_platformSpacing = platformSpacing;
		m_angle = angle;
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

        createPlaceItemsByOutlines();

        qtuser_core::ProgressorTracer tracer(progressor);
        if (!m_insert && m_activeItems.size() == 0)
        {
            tracer.failed("Nest2DJobEx::work invalid input.");
            return;
        }

        if (m_insert)
        {
            m_activeItems.push_back(m_insert);
        }

        doLayout(tracer);

        afterWork();
    }

    void Nest2DJobEx::beforeWork()
    {
    }

    void Nest2DJobEx::afterWork()
    {
    }

    void Nest2DJobEx::createPlaceItemsByOutlines()
    {
        for (int i = 0; i < m_fixedOutlines.size(); i++)
        {
            m_fixedItems.push_back(new PlaceItemEx(m_fixedOutlines[i], this));
        }

        for (int k = 0; k < m_activeOutlines.size(); k++)
        {
            m_activeItems.push_back(new PlaceItemEx(m_activeOutlines[k], this));
        }
    }

    void Nest2DJobEx::doLayout(ccglobal::Tracer& tracer)
    {
        YDefaultBinExtendStrategy binExtendStrategy(m_box, m_panDistance);

        PlacerParameter parameter;
		parameter.itemGap = m_modelspacing;
		parameter.binItemGap = m_platformSpacing;
		parameter.rotate = true;
		parameter.rotateAngle = m_angle;
        if (!cxkernel::isReleaseVersion())
        {
            QString cacheName = cxkernel::createNewAlgCache("autolayout");
			parameter.fileName = cacheName.toLocal8Bit().constData();
        }

        std::vector<nestplacer::PlacerItem*> fixed;
        std::vector<nestplacer::PlacerItem*> actives;
        std::vector<PlacerResultRT> results;

        for (PlaceItemEx* fItem : m_fixedItems)
        {
            fixed.push_back(fItem);
        }

        for (PlaceItemEx* aItem : m_activeItems)
        {
            actives.push_back(aItem);
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

    }
}