#ifndef QTUSER_3D_XENTITY_1679973441774_H
#define QTUSER_3D_XENTITY_1679973441774_H
#include "cxkernel/cxkernelinterface.h"
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QParameter>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QEffect>

namespace cxkernel
{
	class XEffect;
	class CXKERNEL_API XEntity : public Qt3DCore::QEntity
	{
		Q_OBJECT
	public:
		XEntity(Qt3DCore::QNode* parent = nullptr);
		virtual ~XEntity();

		Qt3DRender::QParameter* setParameter(const QString& name, const QVariant& value);
		void setEffect(XEffect* effect);
		void setPose(const QMatrix4x4& matrix);
	protected:
		Qt3DRender::QMaterial* m_material;
		Qt3DCore::QTransform* m_transform;
		Qt3DRender::QGeometryRenderer* m_geometryRenderer;
	};
}

#endif // QTUSER_3D_XENTITY_1679973441774_H