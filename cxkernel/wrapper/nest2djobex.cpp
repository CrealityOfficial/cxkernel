#include "nest2djobex.h"
#include "qtusercore/module/progressortracer.h"

#if USE_NESTPLACER
#include "nestplacer/nestplacer.h"
#endif

#include "nestplacer/placer.h"
#include "cxkernel/interface/constinterface.h"
#include "cxkernel/interface/cacheinterface.h"

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

    void Nest2DJobEx::setInsertItem(PlaceItemEx* item)
    {
        m_insert = item;
    }

    void Nest2DJobEx::setPlaceItems(const std::vector<nestplacer::PlacerItem*>& fixedItems, const std::vector<nestplacer::PlacerItem*>& activeItems)
    {
        m_fixedItems = fixedItems;
        m_activeItems = activeItems;
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
        trimesh::box3 b1 = item1->globalBox();
        trimesh::box3 b2 = item2->globalBox();
        return  b1.size().z > b2.size().z;
    }

    // invoke from main thread
    void Nest2DJobEx::successed(qtuser_core::Progressor* progressor)
    {
    }

    void Nest2DJobEx::work(qtuser_core::Progressor* progressor)
    {
        beforeWork();

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
        m_fixedItems.clear();
        m_activeItems.clear();
        m_results.clear();
    }

    void Nest2DJobEx::afterWork()
    {
        if (m_results.empty())
            return;

        int i = 0;
        int j = 0;

        for (; i < m_fixedItems.size(); i++)
        {
            PlaceItemEx* aPlaceItem = (PlaceItemEx*)(m_fixedItems[i]);
            aPlaceItem->setNestResult(m_results[i]);
        }

        for (; j < m_activeItems.size(); j++)
        {
            PlaceItemEx* aPlaceItem = (PlaceItemEx*)(m_activeItems[j]);
            aPlaceItem->setNestResult(m_results[i]);
            i++;
        }
    }

    void Nest2DJobEx::doLayout(ccglobal::Tracer& tracer)
    {
        YDefaultBinExtendStrategy binExtendStrategy(m_box, m_panDistance);

        PlacerParameter parameter;

        if (!cxkernel::isReleaseVersion())
        {
            QString cacheName = cxkernel::createNewAlgCache("autolayout");
            parameter.fileName = cacheName.toLocal8Bit().constData();
        }

        place(m_fixedItems, m_activeItems, parameter, m_results, binExtendStrategy);
    }
}