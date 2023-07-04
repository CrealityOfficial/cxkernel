#ifndef CXKERNEL_ANTIALIASING_ENTITY_1681992284923_H
#define CXKERNEL_ANTIALIASING_ENTITY_1681992284923_H
#include "cxkernel/cxkernelinterface.h"
#include "qtuser3d/refactor/xentity.h"
#include "qcxutil/trimesh2/renderprimitive.h"
#include <QVector2D>
#include <Qt3DRender/QTexture>

namespace cxkernel
{
	class CXKERNEL_API AntiAliasingEntity : public qtuser_3d::XEntity
	{
	public:
		AntiAliasingEntity(Qt3DCore::QNode* parent = nullptr);
		virtual ~AntiAliasingEntity();

		void setTextureSize(const QVector2D& theSize);
		void setTextureId(quint16 texId);
		void setShareTexture(Qt3DRender::QSharedGLTexture* shareTexture);
		void setAntiFlag(int iFlag);
	protected:
		Qt3DRender::QParameter* m_textureSize;
		Qt3DRender::QParameter* m_textureId;
		Qt3DRender::QParameter* m_antiFlag;
	};
}

#endif // CXKERNEL_ANTIALIASING_ENTITY_1681992284923_H