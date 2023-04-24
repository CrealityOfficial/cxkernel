#ifndef CXKERNEL_SURFACEQUADENTITY_1682318036139_H
#define CXKERNEL_SURFACEQUADENTITY_1682318036139_H
#include "cxkernel/cxkernelinterface.h"
#include "qtuser3d/refactor/xentity.h"
#include "qcxutil/trimesh2/renderprimitive.h"

namespace cxkernel
{
	class CXKERNEL_API SurfaceQuadEntity : public qtuser_3d::XEntity
	{
	public:
		SurfaceQuadEntity(Qt3DCore::QNode* parent = nullptr);
		virtual ~SurfaceQuadEntity();

		void setColor(const QVector4D& color);
	protected:
		Qt3DRender::QParameter* m_color;
	};
}

#endif // CXKERNEL_SURFACEQUADENTITY_1682318036139_H