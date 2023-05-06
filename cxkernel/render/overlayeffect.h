#ifndef CXKERNEL_OVERLAYEFFECT_1681819876499_H
#define CXKERNEL_OVERLAYEFFECT_1681819876499_H
#include "cxkernel/cxkernelinterface.h"
#include "qtuser3d/refactor/xeffect.h"
#include <QtGui/QVector4D>

namespace cxkernel
{
	class CXKERNEL_API OverlayEffect : public qtuser_3d::XEffect
	{
	public:
		OverlayEffect(Qt3DCore::QNode* parent = nullptr);
		virtual ~OverlayEffect();

	};
}

#endif // CXKERNEL_SUPPORTPOSEFFECT_1681819876499_H