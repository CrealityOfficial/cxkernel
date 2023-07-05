#include "modelentity.h"

namespace cxkernel
{
	ModelEntity::ModelEntity(Qt3DCore::QNode* parent)
		:PickXEntity(parent)
	{
		m_effect = new ModelPhongEffect(this);
		m_effect->setRenderEffectMode(cxkernel::RenderEffectMode::rem_face);

		setEffect(m_effect);
		
		m_effect->addPassFilter(0, "view");
		m_effect->addPassFilter(1, "pick");
	}

	ModelEntity::~ModelEntity()
	{

	}

	ModelPhongEffect* ModelEntity::mEffect()
	{
		return m_effect;
	}
}