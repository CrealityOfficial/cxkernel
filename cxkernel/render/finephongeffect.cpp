#include "finephongeffect.h"
#include "qtuser3d/refactor/xrenderpass.h"

namespace cxkernel
{
	FinePhongEffect::FinePhongEffect(Qt3DCore::QNode* parent)
		: XEffect(parent)
	{
		addRenderPass(new qtuser_3d::XRenderPass("phong"));
		addPassFilter(0, "view");
	}

	FinePhongEffect::~FinePhongEffect()
	{

	}

}