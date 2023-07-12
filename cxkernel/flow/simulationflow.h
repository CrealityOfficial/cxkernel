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
	typedef std::function<void(const QString& fileName)> circleLoadFunc;
	class CXKERNEL_API SimulationFlow : public qtuser_3d::XRenderGraph
		, public cxkernel::ModelNDataProcessor
	{
		Q_OBJECT
	public:
		SimulationFlow(Qt3DCore::QNode* parent = nullptr);
		virtual ~SimulationFlow();

		void init();
		void uninit();
	protected:
		virtual void initialize();
		virtual void unInitialize();

		CXModelPtr model(int index);

		void addMesh(TriMeshPtr mesh, bool toCenter = false);
		void pushModel(ModelNDataPtr data, bool lowerZ = true);
		void pushModels(const QList<ModelNDataPtr>& datas, bool lowerZ = true);
		void clearModels();

		QList<CXModelPtr> models();

		void showPrinter(bool show);

		void viewBox(const trimesh::box3& box);
		void viewPrinter();
		Q_INVOKABLE void viewModels(bool visible);

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
		void _triangle(const QString& name, const std::vector<trimesh::vec3>& tris);
		void _triangle(qtuser_3d::XEntity* entity, const std::vector<trimesh::vec3>& tris);

		cxkernel::PureEntity* createPure(const QString& name);

		CXModelPtr pick(const QPoint& point, int* primitiveID = nullptr);

		void setModelRenderEffectMode(CXModelPtr model, RenderEffectMode mode);
		void circleDirectory(const QString& directory, circleLoadFunc func);

		void insert(CXModelPtr model);
	protected:
		qtuser_3d::ColorPicker* m_picker;
		qtuser_3d::Selector* m_selector;
		QList<CXModelPtr> m_models;
		PrinterEntity* m_printer;

		QMap<QString, qtuser_3d::XEntity*> m_namedEntities;
	};
}
#endif // CXKERNEL_SIMULATIONFLOW_1684896500824_H