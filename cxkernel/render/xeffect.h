#ifndef QTUSER_3D_XEFFECT_1679973441776_H
#define QTUSER_3D_XEFFECT_1679973441776_H
#include "cxkernel/cxkernelinterface.h"
#include <Qt3DRender/QEffect>
#include <Qt3DRender/QParameter>

namespace cxkernel
{
	class XRenderPass;
	class CXKERNEL_API XEffect : public Qt3DRender::QEffect
	{
		Q_OBJECT
	public:
		XEffect(Qt3DCore::QNode* parent = nullptr);
		virtual ~XEffect();

		Qt3DRender::QParameter* setParameter(const QString& name, const QVariant& value);
		void addRenderPass(XRenderPass* pass);
	protected:
		Qt3DRender::QTechnique* m_technique;
	};
}

#endif // QTUSER_3D_XEFFECT_1679973441776_H