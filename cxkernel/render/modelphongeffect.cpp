#include "modelphongeffect.h"

namespace cxkernel
{
	ModelPhongEffect::ModelPhongEffect(Qt3DCore::QNode* parent)
		: XEffect(parent)
	{
		addRenderPass(new qtuser_3d::XRenderPass("modelphong"));

		QVariantList values;
		values << QVector4D(1.0f, 0.54f, 0.0f, 1.0f)
			   << QVector4D(1.0f, 0.54f, 0.0f, 1.0f)
			   << QVector4D(1.0f, 0.54f, 0.0f, 1.0f)
			   << QVector4D(1.0f, 0.54f, 0.0f, 1.0f)
			   << QVector4D(1.0f, 0.54f, 0.0f, 1.0f)
			   << QVector4D(1.0f, 0.54f, 0.0f, 1.0f);

		setParameter("stateColors[0]", values);

		QVector4D ambient(0.3f, 0.3f, 0.3f, 1.0f);
		QVector4D diffuse(0.65f, 0.65f, 0.65f, 1.0f);
		QVector4D specular(0.3f, 0.3f, 0.3f, 1.0f);

		setParameter("ambient", ambient);
		setParameter("diffuse", diffuse);
		setParameter("specular", specular);
	}

	ModelPhongEffect::~ModelPhongEffect()
	{

	}
}