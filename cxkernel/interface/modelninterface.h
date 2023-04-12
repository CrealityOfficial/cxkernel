#ifndef CXKERNEL_MODELNINTERFACE_1681280986880_H
#define CXKERNEL_MODELNINTERFACE_1681280986880_H
#include "cxkernel/data/modelndata.h"

namespace cxkernel
{
	CXKERNEL_API void addModelFromCreateInput(const ModelCreateInput& input);
	CXKERNEL_API void setModelNDataProcessor(ModelNDataProcessor* processor);
}

#endif // CXKERNEL_MODELNINTERFACE_1681280986880_H