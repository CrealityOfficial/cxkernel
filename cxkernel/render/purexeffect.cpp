#include "purexeffect.h"
#include "qtuser3d/refactor/xrenderpass.h"

namespace cxkernel
{
	PureXEffect::PureXEffect(Qt3DCore::QNode* parent)
		: XEffect(parent)
	{
		m_color = setParameter("color", QVector4D(0.5f, 0.5f, 0.5f, 1.0f));
		addRenderPass(new qtuser_3d::XRenderPass("pure"));
	}

	PureXEffect::~PureXEffect()
	{

	}

	void PureXEffect::setColor(const QVector4D& color)
	{
		m_color->setValue(color);
	}
}