#ifndef QTUSER_3D_XRENDERGRAPH_1679973441799_H
#define QTUSER_3D_XRENDERGRAPH_1679973441799_H
#include "cxkernel/cxkernelinterface.h"
#include "qtuser3d/framegraph/rendergraph.h"
#include <Qt3DRender/QClearBuffers>
#include <Qt3DRender/QViewport>
#include <Qt3DRender/QCameraSelector>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QRenderPassFilter>
#include <Qt3DRender/QSortPolicy>
#include <Qt3DRender/QRenderSurfaceSelector>
#include <QtGui/QOffscreenSurface>

namespace cxkernel
{
	class CXKERNEL_API XRenderGraph : public qtuser_3d::RenderGraph
	{
	public:
		XRenderGraph(Qt3DCore::QNode* parent = nullptr);
		virtual ~XRenderGraph();

		void setClearColor(const QColor& color);
		void setViewport(const QRectF& rect);
		void updateSurfaceSize(const QSize& size);
	protected:
		void updateRenderSize(const QSize& size) override;

		Qt3DCore::QEntity* rootEntity();
	protected:
		Qt3DRender::QRenderSurfaceSelector* m_surfaceSelector;
		QOffscreenSurface* m_offSurface;
		Qt3DRender::QViewport* m_viewPort;
		Qt3DRender::QCameraSelector* m_cameraSelector;
		Qt3DRender::QClearBuffers* m_clearBuffer;

		Qt3DCore::QEntity* m_rootEntity;
		Qt3DRender::QCamera* m_camera;
	};
}

#endif // QTUSER_3D_XRENDERGRAPH_1679973441799_H