#ifndef CXKERNEL_MODELPHONGEFFECT_1681899751633_H
#define CXKERNEL_MODELPHONGEFFECT_1681899751633_H
#include "cxkernel/cxkernelinterface.h"
#include "qtuser3d/refactor/xeffect.h"
#include <QtGui/QVector4D>

namespace cxkernel
{
	class CXKERNEL_API ModelPhongEffect : public qtuser_3d::XEffect
	{
	public:
		ModelPhongEffect(Qt3DCore::QNode* parent = nullptr);
		virtual ~ModelPhongEffect();

	protected:
	};
}

#endif // CXKERNEL_MODELPHONGEFFECT_1681899751633_H