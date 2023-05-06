#include "modelsimpleeffect.h"
#include "qtuser3d/refactor/xrenderpass.h"

namespace cxkernel
{
	ModelSimpleEffect::ModelSimpleEffect(Qt3DCore::QNode* parent)
		: XEffect(parent)
	{
		addRenderPass(new qtuser_3d::XRenderPass("modelsimple"));
		addPassFilter(0, "modelcapture");

		setParameter("ambient", QVector4D(0.8f, 0.8f, 0.8f, 1.0f));
		setParameter("diffuse", QVector4D(0.5f, 0.5f, 0.5f, 1.0f));
		setParameter("specular", QVector4D(0.8f, 0.8f, 0.8f, 1.0f));
		setParameter("stateColors", QVector4D(0.55f, 0.55f, 0.55f, 1.0f));

	}

	ModelSimpleEffect::~ModelSimpleEffect()
	{

	}

}