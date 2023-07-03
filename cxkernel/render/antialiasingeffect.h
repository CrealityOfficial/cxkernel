#ifndef CXKERNEL_ANTIALIASING_EFFECT_1681819876499_H
#define CXKERNEL_ANTIALIASING_EFFECT_1681819876499_H
#include "cxkernel/cxkernelinterface.h"
#include "qtuser3d/refactor/xeffect.h"
#include <QtGui/QVector4D>

namespace cxkernel
{
	class CXKERNEL_API AntiAliasingEffect : public qtuser_3d::XEffect
	{
	public:
		AntiAliasingEffect(Qt3DCore::QNode* parent = nullptr);
		virtual ~AntiAliasingEffect();

		void setColor(const QVector4D& color);
	protected:
		Qt3DRender::QParameter* m_color;
	};
}

#endif // CXKERNEL_ANTIALIASING_EFFECT_1681819876499_H