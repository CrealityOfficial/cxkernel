/**
 * @file modelninterface.h
 * @author zenggui (anoob@sina.cn)
 * @brief 
 * @version 0.1
 * @date 2023-06-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CXKERNEL_MODELNINTERFACE_1681280986880_H
#define CXKERNEL_MODELNINTERFACE_1681280986880_H
#include "cxkernel/data/modelndata.h"

namespace cxkernel
{
	CXKERNEL_API void addModelFromCreateInput(const ModelCreateInput& input);
	CXKERNEL_API void setModelNDataProcessor(ModelNDataProcessor* processor);

	CXKERNEL_API void setLoadParam(const ModelNDataCreateParam& param);
}

#endif // CXKERNEL_MODELNINTERFACE_1681280986880_H