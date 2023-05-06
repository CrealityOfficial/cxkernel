#ifndef CXKERNEL_MODELSIMPLEEFFECT_1681819876499_H
#define CXKERNEL_MODELSIMPLEEFFECT_1681819876499_H
#include "cxkernel/cxkernelinterface.h"
#include "qtuser3d/refactor/xeffect.h"
#include <QtGui/QVector4D>

namespace cxkernel
{
	class CXKERNEL_API ModelSimpleEffect : public qtuser_3d::XEffect
	{
	public:
		ModelSimpleEffect(Qt3DCore::QNode* parent = nullptr);
		virtual ~ModelSimpleEffect();

	protected:

	};
}

#endif // CXKERNEL_MODELSIMPLEEFFECT_1681819876499_H