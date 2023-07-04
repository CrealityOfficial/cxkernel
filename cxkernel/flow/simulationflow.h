#ifndef CXKERNEL_SIMULATIONFLOW_1684896500824_H
#define CXKERNEL_SIMULATIONFLOW_1684896500824_H
#include "qtuser3d/framegraph/xrendergraph.h"
#include "cxkernel/data/modelndata.h"
#include "cxkernel/render/modelentity.h"
#include "cxkernel/flow/cxmodel.h"
#include "cxkernel/render/printerentity.h"
#include <QtCore/QMap>

namespace cxkernel
{
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

		void pushModel(ModelNDataPtr data, bool lowerZ = true);
		void pushModels(const QList<ModelNDataPtr>& datas, bool lowerZ = true);
		void clearModels();

		QList<CXModelPtr> models();

		void showPrinter(bool show);

		void viewBox(const trimesh::box3& box);
		void viewPrinter();
	protected:
		void process(ModelNDataPtr data) override;
		virtual void onModelLoaded(ModelNDataPtr data);
		virtual void onCXModelCreated(CXModelPtr model);

		void _add(const QString& name, qtuser_3d::XEntity* entity);
		void _remove(const QString& name);
		qtuser_3d::XEntity* _find(const QString& name);
		cxkernel::PureEntity* createPure(const QString& name);
	protected:
		QList<CXModelPtr> m_models;
		PrinterEntity* m_printer;

		QMap<QString, qtuser_3d::XEntity*> m_namedEntities;
	};
}
#endif // CXKERNEL_SIMULATIONFLOW_1684896500824_H