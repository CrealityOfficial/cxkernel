#include "xrendergraph.h"

namespace cxkernel
{
	XRenderGraph::XRenderGraph(Qt3DCore::QNode* parent)
		: RenderGraph(parent)
	{
		m_surfaceSelector = new Qt3DRender::QRenderSurfaceSelector(this);
		m_offSurface = new QOffscreenSurface(nullptr);
		m_offSurface->create();
		m_surfaceSelector->setSurface(m_offSurface);

		m_viewPort = new Qt3DRender::QViewport(m_surfaceSelector);
		m_viewPort->setNormalizedRect(QRectF(0.0f, 0.0f, 1.0f, 1.0f));

		m_cameraSelector = new Qt3DRender::QCameraSelector(m_viewPort);

		m_clearBuffer = new Qt3DRender::QClearBuffers(m_cameraSelector);
		m_clearBuffer->setClearColor(QColor(120, 120, 120, 255));
		m_clearBuffer->setClearStencilValue(0x0);
		m_clearBuffer->setBuffers(Qt3DRender::QClearBuffers::BufferType::ColorDepthStencilBuffer);

		m_rootEntity = new Qt3DCore::QEntity(this);
		m_camera = new Qt3DRender::QCamera(this);
		m_cameraSelector->setCamera(m_camera);
	}

	XRenderGraph::~XRenderGraph()
	{

	}

	void XRenderGraph::setClearColor(const QColor& color)
	{
		m_clearBuffer->setClearColor(color);
	}

	void XRenderGraph::setViewport(const QRectF& rect)
	{
		m_viewPort->setNormalizedRect(rect);
	}

	void XRenderGraph::updateSurfaceSize(const QSize& size)
	{
		m_surfaceSelector->setExternalRenderTargetSize(size);
	}

	Qt3DCore::QEntity* XRenderGraph::sceneGraph()
	{
		return m_rootEntity;
	}

	void XRenderGraph::updateRenderSize(const QSize& size)
	{
		updateSurfaceSize(size);
	}

	Qt3DCore::QEntity* XRenderGraph::rootEntity()
	{
		return m_rootEntity;
	}
}