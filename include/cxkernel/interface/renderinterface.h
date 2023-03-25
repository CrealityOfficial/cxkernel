#ifndef CX_KERNEL_RENDERINTERFACE_1594447238062_H
#define CX_KERNEL_RENDERINTERFACE_1594447238062_H
#include "cxkernel/cxkernelinterface.h"
#include "qtuser3d/framegraph/rendergraph.h"

namespace cxkernel
{
	CXKERNEL_API void renderRenderGraph(qtuser_3d::RenderGraph* graph);
	CXKERNEL_API void registerRenderGraph(qtuser_3d::RenderGraph* graph);

}
#endif // CX_KERNEL_RENDERINTERFACE_1594447238062_H