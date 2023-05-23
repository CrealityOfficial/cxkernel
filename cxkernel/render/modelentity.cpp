#include "modelentity.h"

namespace cxkernel
{
	ModelEntity::ModelEntity(Qt3DCore::QNode* parent)
		:XEntity(parent)
	{
		m_effect = new ModelPhongEffect(this);
		m_effect->setRenderEffectMode(cxkernel::RenderEffectMode::rem_face);

		setEffect(m_effect);
	}

	ModelEntity::~ModelEntity()
	{

	}
}