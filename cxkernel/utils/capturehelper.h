#ifndef _CAPTUREHELPER_1596613436897_H
#define _CAPTUREHELPER_1596613436897_H
#include "cxkernel/cxkernelinterface.h"
#include <Qt3DRender/QFrameGraphNode>
#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QTexture>
#include <Qt3DRender/QEffect>

#include "qtuser3d/math/box3d.h"
#include "cxkernel/data/captureSetupData.h"
#include "cxkernel/data/capturetask.h"

#include "cxkernel/render/pureentity.h"

namespace qtuser_3d
{
	class ColorPicker;
	class TextureRenderTarget;
	class XEntity;
}

namespace cxkernel
{
	class CaptureEntity;

	class CXKERNEL_API CaptureHelper : public QObject
	{
		Q_OBJECT
	public:
		CaptureHelper(QObject* parent = nullptr);
		virtual ~CaptureHelper();

		void resize(qtuser_3d::Box3D& box, int resolution_x, int resolution_y);
		void attachToMainGraph(Qt3DRender::QFrameGraphNode* frameGraph, Qt3DCore::QNode* sceneGraph);
		void detachFromMainGraph();
		void clear();

		void setFormat(Qt3DRender::QAbstractTexture::TextureFormat format);
		void capture(Qt3DRender::QGeometry* geometry, QString index, captureCallbackFunc func);

		void captureModel(const CaptureSetupData& captureSetInfo, captureCallbackFunc func, bool bProject = false);

		void capturePreview(captureCallbackFunc func, QVector3D& viewCenter, QVector3D& upVector, QVector3D& eyePosition, QMatrix4x4& projectionMatrix, QString name = "-1");
		void onPreviewCaptureFinish();

		void captureModelComplete();

		qtuser_3d::ColorPicker* colorPicker();

	protected:
		void captureComplete(QImage& image);

		//void createCaptureEffect();

	protected:
		qtuser_3d::ColorPicker* m_colorPicker;
		cxkernel::PureEntity* m_basicEntity;
		qtuser_3d::TextureRenderTarget* m_renderTarget;

		Qt3DCore::QNode* m_sceneGraph;

		//qtuser_3d::BasicEntity* m_captureEntity;
		//Qt3DRender::QEffect* m_captureEffect;

		cxkernel::CaptureEntity* m_captureEntity;

		QString m_index;
		captureCallbackFunc m_func;

	};

}

#endif // _CAPTUREHELPER_1596613436897_H