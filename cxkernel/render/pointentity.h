#ifndef CXKERNEL_POINTENTITY_1683186457676_H
#define CXKERNEL_POINTENTITY_1683186457676_H
#include "cxkernel/cxkernelinterface.h"
#include "qtuser3d/refactor/xentity.h"
#include "qcxutil/trimesh2/renderprimitive.h"
#include <Qt3DRender/QPointSize>

namespace cxkernel
{
	class CXKERNEL_API PointEntity : public qtuser_3d::XEntity
	{
	public:
		PointEntity(Qt3DCore::QNode* parent = nullptr);
		virtual ~PointEntity();

		void setColor(const QVector4D& color);
		void setPointSize(float size);
		void setPoints(const std::vector<trimesh::vec3>& points);
	protected:
		Qt3DRender::QParameter* m_color;
		Qt3DRender::QPointSize* m_pointSizeState;
	};
}

#endif // CXKERNEL_POINTENTITY_1683186457676_H