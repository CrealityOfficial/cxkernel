#ifndef _CAPTURECONTAINER_1596608352857_H
#define _CAPTURECONTAINER_1596608352857_H
#include "cxkernel/cxkernelinterface.h"
#include <QtCore/QObject>
#include <Qt3DRender/QFrameGraphNode>
#include <Qt3DRender/QGeometry>
#include "qtuser3d/math/box3d.h"
#include "qcxutil/trimesh2/q3drender.h"


namespace cxkernel
{

	class CaptureTask;
	class CaptureHelper;

	class CXKERNEL_API CaptureContainer : public QObject
	{
		Q_OBJECT
	public:
		CaptureContainer(QObject* parent = nullptr);
		virtual ~CaptureContainer();

		void setRoot(Qt3DRender::QFrameGraphNode* frameGrpha, Qt3DCore::QNode* sceneGraph);

		void start(qtuser_3d::Box3D& box, int resolution_x, int resolution_y, Qt3DRender::QFrameGraphNode* frameGraph, Qt3DCore::QNode* sceneGraph);
		void finish();
		void executePreivew(cxkernel::CaptureTask* task, QVector3D& viewCenter, QVector3D& upVector, QVector3D& eyePosition, QMatrix4x4& projectionMatrix);
		void onPreviewCaptureFinish();

		void captureModel(cxkernel::CaptureTask* task, QString model_name, Qt3DRender::QGeometry* geometry, QMatrix4x4 entityPos, qtuser_3d::Box3D box);
		void captureProjectModels(cxkernel::CaptureTask* task, QString model_name, qtuser_3d::Box3D box);
		void captureScene(cxkernel::CaptureTask* task, QString scene_name, qtuser_3d::Box3D box);

	public slots:
		void captureModelComplete();
	protected:

		cxkernel::CaptureHelper* m_previewHelper;
	};

}

#endif // _CAPTURECONTAINER_1596608352857_H