#ifndef CXKERNEL_AUTOLAYOUT_NEST2D_EX_JOB_H
#define CXKERNEL_AUTOLAYOUT_NEST2D_EX_JOB_H
#include "cxkernel/data/header.h"

#include "qtusercore/module/job.h"
#include "ccglobal/tracer.h"
#include "nestplacer/placer.h"

namespace cxkernel
{

    class PlaceItemEx : public nestplacer::PlacerItem
    {
    public:
        virtual ~PlaceItemEx() {}

        virtual trimesh::vec3 position() = 0;
        virtual trimesh::box3 globalBox() = 0;
        virtual std::vector<trimesh::vec3> outLine(bool global = false) = 0;
        virtual std::vector<trimesh::vec3> outLine_concave() = 0;

        void setNestResult(const nestplacer::PlacerResultRT& _result) { result = _result; }
    public:
        nestplacer::PlacerResultRT result;
    };

    class CXKERNEL_API Nest2DJobEx : public qtuser_core::Job
    {
        Q_OBJECT
    public:
        Nest2DJobEx(QObject* parent = nullptr);
        virtual ~Nest2DJobEx();

        void setBounding(const trimesh::box3& box);
        void setPanDistance(float distance);
        void setInsertItem(PlaceItemEx* item);
        void setPlaceItems(const std::vector<nestplacer::PlacerItem*>& fixedItems, const std::vector<nestplacer::PlacerItem*>& activeItems);
    protected:
        QString name();
        QString description();
        void failed();                        // invoke from main thread
        void successed(qtuser_core::Progressor* progressor);                     // invoke from main thread
        void work(qtuser_core::Progressor* progressor);    // invoke from worker thread

        virtual void beforeWork();
        virtual void afterWork();
        void doLayout(ccglobal::Tracer& tracer);
    protected:
        trimesh::box3 m_box;

        PlaceItemEx* m_insert;

        float m_panDistance;

        std::vector<nestplacer::PlacerItem*> m_fixedItems;
        std::vector<nestplacer::PlacerItem*> m_activeItems;
        std::vector<nestplacer::PlacerResultRT> m_results;
    };
}

#endif // CXKERNEL_AUTOLAYOUT_NEST2D_EX_JOB_H
