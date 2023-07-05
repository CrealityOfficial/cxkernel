#ifndef CXKERNEL_MODELENTITY_1681899751632_H
#define CXKERNEL_MODELENTITY_1681899751632_H
#include "cxkernel/cxkernelinterface.h"
#include "qtuser3d/refactor/pxentity.h"
#include "cxkernel/render/modelphongeffect.h"

namespace cxkernel
{
	class CXKERNEL_API ModelEntity : public qtuser_3d::PickXEntity
	{
	public:
		ModelEntity(Qt3DCore::QNode* parent = nullptr);
		virtual ~ModelEntity();

		ModelPhongEffect* mEffect();
	protected:
		ModelPhongEffect* m_effect;
	};
}

#endif // CXKERNEL_MODELENTITY_1681899751632_H