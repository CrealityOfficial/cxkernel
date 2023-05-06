#include "supportposeffect.h"
#include "qtuser3d/refactor/xrenderpass.h"

namespace cxkernel
{
	SupportPosEffect::SupportPosEffect(Qt3DCore::QNode* parent)
		: XEffect(parent)
	{
		addRenderPass(new qtuser_3d::XRenderPass("supportpos"));
	}

	SupportPosEffect::~SupportPosEffect()
	{

	}

}