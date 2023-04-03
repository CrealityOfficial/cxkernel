#ifndef QTUSER_3D_XRENDERPASS_1679990543678_H
#define QTUSER_3D_XRENDERPASS_1679990543678_H
#include "cxkernel/cxkernelinterface.h"
#include <Qt3DRender/QRenderPass>
#include <Qt3DRender/QCullFace>
#include <Qt3DRender/QBlendEquationArguments>
#include <Qt3DRender/QStencilOperationArguments>
#include <Qt3DRender/QStencilTestArguments>
#include <Qt3DRender/QDepthTest>
#include <Qt3DRender/QNoDepthMask>
#include <Qt3DRender/QParameter>

namespace cxkernel
{
	class CXKERNEL_API XRenderPass : public Qt3DRender::QRenderPass
	{
	public:
		XRenderPass(const QString& shaderName, Qt3DCore::QNode* parent = nullptr);
		virtual ~XRenderPass();

		void addFilterKeyMask(const QString& key, int mask);
		Qt3DRender::QParameter* setParameter(const QString& name, const QVariant& value);
	};
}

#endif // QTUSER_3D_XRENDERPASS_1679990543678_H