#include "modelsimpleeffect.h"
#include "qtuser3d/refactor/xrenderpass.h"

namespace cxkernel
{
	ModelSimpleEffect::ModelSimpleEffect(Qt3DCore::QNode* parent)
		: XEffect(parent)
	{
		addRenderPass(new qtuser_3d::XRenderPass("phong"));
		addPassFilter(0, "modelcapture");

		setParameter("color", QVariant::fromValue(QVector4D(0.55f, 0.55f, 0.55f, 1.0f)));
		setParameter("ambient", QVariant::fromValue(QVector4D(0.8f, 0.8f, 0.8f, 1.0f)));
		setParameter("diffuse", QVariant::fromValue(QVector4D(0.5f, 0.5f, 0.5f, 1.0f)));
		setParameter("specular", QVariant::fromValue(QVector4D(0.8f, 0.8f, 0.8f, 1.0f)));
		setParameter("specularPower", QVariant::fromValue(12.0));

	}

	ModelSimpleEffect::~ModelSimpleEffect()
	{

	}

}