#include "overlayeffect.h"
#include "qtuser3d/refactor/xrenderpass.h"

namespace cxkernel
{
	OverlayEffect::OverlayEffect(Qt3DCore::QNode* parent)
		: XEffect(parent)
	{
		addRenderPass(new qtuser_3d::XRenderPass("overlay"));
		addPassFilter(0, QStringLiteral("view"));
	}

	OverlayEffect::~OverlayEffect()
	{

	}

}