#ifndef _CREATIVE_KERNEL_MODEL_FROM_MESH_JOB_1590984808257_H
#define _CREATIVE_KERNEL_MODEL_FROM_MESH_JOB_1590984808257_H
#include "qtusercore/module/job.h"
#include "data/geometrydata.h"

namespace creative_kernel
{
	class BASIC_KERNEL_API ModelFromMeshJob: public qtuser_core::Job
	{
	public:
		ModelFromMeshJob(QObject* parent = nullptr);
		virtual ~ModelFromMeshJob();

		void setInput(ModelCreateInput input);
	protected:
		QString name();
		QString description();
		void failed();                        // invoke from main thread
		void successed(qtuser_core::Progressor* progressor);                     // invoke from main thread
		void work(qtuser_core::Progressor* progressor);    // invoke from worker thread

	protected:
		ModelCreateInput m_input;
		ModelNDataPtr m_data;
	};
}
#endif // _CREATIVE_KERNEL_MODEL_FROM_MESH_JOB_1590984808257_H
