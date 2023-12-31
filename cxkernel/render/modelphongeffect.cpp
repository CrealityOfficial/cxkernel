#include "modelphongeffect.h"

namespace cxkernel
{
	ModelPhongEffect::ModelPhongEffect(Qt3DCore::QNode* parent)
		: XEffect(parent)
	{
		qtuser_3d::XRenderPass* pass = new qtuser_3d::XRenderPass("modelphong");
		pass->setPassCullFace();
		addRenderPass(pass);

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

		m_remParameter = setParameter("renderModel", 1);

		qtuser_3d::XRenderPass* pickPass = new qtuser_3d::XRenderPass("pickFace");
		pickPass->setPassCullFace();
		addRenderPass(pickPass);
		setPassBlend(1, Qt3DRender::QBlendEquationArguments::One, Qt3DRender::QBlendEquationArguments::Zero);
	}

	ModelPhongEffect::~ModelPhongEffect()
	{

	}

	void ModelPhongEffect::setRenderEffectMode(RenderEffectMode mode)
	{
		m_remParameter->setValue((int)mode);
	}
}