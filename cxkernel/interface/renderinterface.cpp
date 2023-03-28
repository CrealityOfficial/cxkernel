#include "cxkernel/interface/renderinterface.h"

#include "cxkernel/kernel/cxkernel.h"
#include "qtuserqml/gl/renderitemwrapper.h"

namespace cxkernel
{
	void renderRenderGraph(qtuser_3d::RenderGraph* graph)
	{
		cxKernel->renderWrapper()->renderRenderGraph(graph);
	}

	void registerRenderGraph(qtuser_3d::RenderGraph* graph)
	{
		cxKernel->renderWrapper()->registerRenderGraph(graph);
	}
}