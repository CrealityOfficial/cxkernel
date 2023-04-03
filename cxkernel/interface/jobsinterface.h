#ifndef _JOBSINTERFACE_1592716998224_H
#define _JOBSINTERFACE_1592716998224_H
#include "cxkernel/cxkernelinterface.h"
#include "qtusercore/module/jobexecutor.h"

namespace cxkernel
{
	CXKERNEL_API bool jobExecutorAvaillable();
	CXKERNEL_API bool executeJobs(const QList<qtuser_core::JobPtr>& jobs, bool front = false);
	CXKERNEL_API bool executeJob(qtuser_core::JobPtr job, bool front = false);
	CXKERNEL_API void addJobTracer(qtuser_core::JobTracer* tracer);
	CXKERNEL_API void removeJobTracer(qtuser_core::JobTracer* tracer);
}
#endif // _JOBSINTERFACE_1592716998224_H