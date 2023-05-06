#include "coloreffect.h"
#include "qtuser3d/refactor/xrenderpass.h"

namespace cxkernel
{
	ColorEffect::ColorEffect(Qt3DCore::QNode* parent)
		: XEffect(parent)
	{
		addRenderPass(new qtuser_3d::XRenderPass("color"));
	}

	ColorEffect::~ColorEffect()
	{

	}

}