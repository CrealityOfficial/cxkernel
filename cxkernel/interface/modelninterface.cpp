#include "modelninterface.h"
#include "cxkernel/kernel/cxkernel.h"
#include "cxkernel/utils/meshloader.h"

namespace cxkernel
{
	void addModelFromCreateInput(const ModelCreateInput& input)
	{
		cxKernel->meshLoader()->addModelFromCreateInput(input);
	}

	void setModelNDataProcessor(ModelNDataProcessor* processor)
	{
		cxKernel->meshLoader()->setModelNDataProcessor(processor);
	}

	void setLoadParam(const ModelNDataCreateParam& param)
	{
		cxKernel->meshLoader()->setParam(param);
	}
}