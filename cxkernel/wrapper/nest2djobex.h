#ifndef CXKERNEL_AUTOLAYOUT_NEST2D_EX_JOB_H
#define CXKERNEL_AUTOLAYOUT_NEST2D_EX_JOB_H
#include "cxkernel/data/header.h"

#include "qtusercore/module/job.h"
#include "ccglobal/tracer.h"

namespace cxkernel
{
    class PlaceItemEx;
	//
    struct  NestResultEx
    {
        trimesh::vec3 rt; // x, y translation  z rotation angle
        int binIndex = 0;
    };

    class CXKERNEL_API Nest2DJobEx : public qtuser_core::Job
    {
        Q_OBJECT
    public:
        Nest2DJobEx(QObject* parent = nullptr);
        virtual ~Nest2DJobEx();

        void setBounding(const trimesh::box3& box);
        void setPanDistance(float distance);

		void setLayoutParameter(float modelSpacing, float platformSpacing, int angle, bool alignMove, bool outlineConcave);
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

        float m_panDistance;

        std::vector<NestResultEx> m_results;

        //each outline relates to one  fixed "nestplacer::PlacerItem"
        std::vector< std::vector<trimesh::vec3> > m_fixedOutlines;

        std::vector< std::vector<trimesh::vec3> > m_activeOutlines;

		float m_modelspacing;
		float m_platformSpacing;
		int m_angle;
		bool m_alignMove;
        bool m_outlineConcave;
    };
}

#endif // CXKERNEL_AUTOLAYOUT_NEST2D_EX_JOB_H
