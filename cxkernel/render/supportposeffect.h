#ifndef CXKERNEL_SUPPORTPOSEFFECT_1681819876499_H
#define CXKERNEL_SUPPORTPOSEFFECT_1681819876499_H
#include "cxkernel/cxkernelinterface.h"
#include "qtuser3d/refactor/xeffect.h"
#include <QtGui/QVector4D>

namespace cxkernel
{
	class CXKERNEL_API SupportPosEffect : public qtuser_3d::XEffect
	{
	public:
		SupportPosEffect(Qt3DCore::QNode* parent = nullptr);
		virtual ~SupportPosEffect();

	};
}

#endif // CXKERNEL_SUPPORTPOSEFFECT_1681819876499_H