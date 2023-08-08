#ifndef CXKERNEL_SIMULATIONFLOW_1684896500824_H
#define CXKERNEL_SIMULATIONFLOW_1684896500824_H
#include "qtuser3d/framegraph/xrendergraph.h"
#include "qtuser3d/framegraph/colorpicker.h"
#include "qtuser3d/module/selector.h"
#include "cxkernel/data/modelndata.h"
#include "cxkernel/render/modelentity.h"
#include "cxkernel/flow/cxmodel.h"
#include "cxkernel/render/printerentity.h"
#include <QtCore/QMap>

namespace cxkernel
{
	typedef std::function<void(const QString&, ccglobal::Tracer*)> circleLoadFunc;
	class CXKERNEL_API SimulationFlow : public qtuser_3d::XRenderGraph
		, public cxkernel::ModelNDataProcessor
	{
		Q_OBJECT
	public:
		SimulationFlow(Qt3DCore::QNode* parent = nullptr);
		virtual ~SimulationFlow();

		void init();
		void uninit();

		virtual void initialize();
		virtual void unInitialize();

		CXModelPtr model(int index);

		void copyMesh(TriMeshPtr mesh);
		void addRawMesh(TriMeshPtr mesh);
		void addMesh(TriMeshPtr mesh, const ModelNDataCreateParam& param = ModelNDataCreateParam());
		void pushModel(ModelNDataPtr data, bool lowerZ = true);
		void pushModels(const QList<ModelNDataPtr>& datas, bool lowerZ = true);
		void clearModels();

		QList<CXModelPtr> models();

		void showPrinter(bool show);

		void viewBox(const trimesh::box3& box);
		void viewPrinter();
		Q_INVOKABLE void viewModels(bool visible);

		Q_INVOKABLE void loadMeshFile(const QString& fileName, bool raw = false);
	public slots:
		void requestCapture(bool capture);
	protected:
		void process(ModelNDataPtr data) override;
		void onResize(const QSize& size) override;

		virtual void onModelLoaded(ModelNDataPtr data);
		virtual void onCXModelCreated(CXModelPtr model);

		void _add(const QString& name, qtuser_3d::XEntity* entity);
		void _remove(const QString& name);
		qtuser_3d::XEntity* _find(const QString& name);

		void _lines(const QString& name, const std::vector<trimesh::vec3>& lines);
		void _lines(qtuser_3d::XEntity* entity, const std::vector<trimesh::vec3>& lines);
		void _lines(qtuser_3d::XEntity* entity, const std::vector<std::vector<trimesh::vec3>>& lines);

		void _triangle(const QString& name, const std::vector<trimesh::vec3>& tris);
		void _triangle(qtuser_3d::XEntity* entity, const std::vector<trimesh::vec3>& tris);

		void _points(const QString& name, const std::vector<trimesh::vec3>& points);
		void _points(qtuser_3d::XEntity* entity, const std::vector<trimesh::vec3>& points);

		void _transform(const QString& name, const QMatrix4x4& m);
		void _transform(qtuser_3d::XEntity* entity, const QMatrix4x4& m);
		void _bind(const QString& name, CXModelPtr model);
		void _bind(qtuser_3d::XEntity* entity, CXModelPtr model);

		cxkernel::PureEntity* createPure(const QString& name);

		CXModelPtr pick(const QPoint& point, int* primitiveID = nullptr);
		qtuser_3d::Pickable* pickPickable(const QPoint& point, int* primitiveID = nullptr);

		void setModelRenderEffectMode(CXModelPtr model, RenderEffectMode mode);
		void circleDirectory(const QString& directory, circleLoadFunc func);
		void ansycBatch(const QString& directory, circleLoadFunc func);

		void insert(CXModelPtr model);

		void runAnonymous(anonymous_work_func workFunc, anonymous_func successFunc);
		void _requestUpdate();
	protected:
		qtuser_3d::ColorPicker* m_picker;
		qtuser_3d::Selector* m_selector;
		QList<CXModelPtr> m_models;
		PrinterEntity* m_printer;

		QMap<QString, qtuser_3d::XEntity*> m_namedEntities;
	};
}
#endif // CXKERNEL_SIMULATIONFLOW_1684896500824_H