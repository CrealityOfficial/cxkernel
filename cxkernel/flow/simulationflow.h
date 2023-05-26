#ifndef CXKERNEL_SIMULATIONFLOW_1684896500824_H
#define CXKERNEL_SIMULATIONFLOW_1684896500824_H
#include "qtuser3d/framegraph/xrendergraph.h"
#include "cxkernel/data/modelndata.h"
#include "cxkernel/render/modelentity.h"
#include "cxkernel/flow/cxmodel.h"
#include "cxkernel/render/printerentity.h"

namespace cxkernel
{
	struct SimulationConfig
	{
		bool showPrinter = true;
	};

	class CXKERNEL_API SimulationFlow : public qtuser_3d::XRenderGraph
		, public cxkernel::ModelNDataProcessor
	{
		Q_OBJECT
	public:
		SimulationFlow(const SimulationConfig& config, Qt3DCore::QNode* parent = nullptr);
		virtual ~SimulationFlow();

		void init();
		void uninit();
	protected:
		virtual void initialize();
		virtual void unInitialize();

		CXModelPtr model(int index);

		void pushModel(ModelNDataPtr data);
		void pushModels(const QList<ModelNDataPtr>& datas);
		void clearModels();
	protected:
		void process(ModelNDataPtr data) override;
		virtual void onModelLoaded(ModelNDataPtr data);
	protected:
		QList<CXModelPtr> m_models;
		PrinterEntity* m_printer;

		SimulationConfig m_config;
	};
}
#endif // CXKERNEL_SIMULATIONFLOW_1684896500824_H