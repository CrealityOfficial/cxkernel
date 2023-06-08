#include "axisentity.h"
#include "qtuser3d/refactor/xeffect.h"

namespace cxkernel
{
	AxisEntity::AxisEntity(Qt3DCore::QNode* parent)
		: XEntity(parent)
	{
		m_entities[0] = new qtuser_3d::XEntity(parent);
		m_entities[1] = new qtuser_3d::XEntity(parent);
		m_entities[2] = new qtuser_3d::XEntity(parent);

		QMatrix4x4 xMatrix;
		xMatrix.setToIdentity();
		xMatrix.rotate(90.0f, 0.0f, 1.0f, 0.0f);
		QMatrix4x4 yMatrix;
		yMatrix.setToIdentity();
		yMatrix.rotate(- 90.0f, 1.0f, 0.0f, 0.0f);
		QMatrix4x4 zMatrix;
		zMatrix.setToIdentity();
		m_entities[0]->setPose(xMatrix);
		m_entities[1]->setPose(yMatrix);
		m_entities[2]->setPose(zMatrix);
	}

	AxisEntity::~AxisEntity()
	{

	}

	void AxisEntity::setAxisEffect(qtuser_3d::XEffect* effect)
	{
		if (!effect)
			return;

		if (!effect->parent())
			effect->setParent(this);

		m_entities[0]->setEffect(effect);
		m_entities[1]->setEffect(effect);
		m_entities[2]->setEffect(effect);
	}

	void AxisEntity::setAxisGeometry(Qt3DRender::QGeometry* geometry)
	{
		if (!geometry)
			return;

		if (!geometry->parent())
			geometry->setParent(this);

		m_entities[0]->setGeometry(geometry);
		m_entities[1]->setGeometry(geometry);
		m_entities[2]->setGeometry(geometry);
	}

	void AxisEntity::setAxisParameter(EAxis eaxis, const QString& name, const QVariant& value)
	{
		m_entities[(int)eaxis]->setParameter(name, value);
	}
}