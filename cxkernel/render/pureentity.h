#ifndef CXKERNEL_PUREENTITY_1681992284923_H
#define CXKERNEL_PUREENTITY_1681992284923_H
#include "cxkernel/cxkernelinterface.h"
#include "qtuser3d/refactor/xentity.h"
#include "qcxutil/trimesh2/renderprimitive.h"

namespace cxkernel
{
	class CXKERNEL_API PureEntity : public qtuser_3d::XEntity
	{
	public:
		PureEntity(Qt3DCore::QNode* parent = nullptr);
		virtual ~PureEntity();

		void setColor(const QVector4D& color);
	protected:
		Qt3DRender::QParameter* m_color;
	};
}

#endif // CXKERNEL_PUREENTITY_1681992284923_H