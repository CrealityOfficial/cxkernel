#ifndef CXKERNEL_SIMULATIONFLOW_1684896500824_H
#define CXKERNEL_SIMULATIONFLOW_1684896500824_H
#include "qtuser3d/framegraph/xrendergraph.h"
#include "cxkernel/data/modelndata.h"
#include "cxkernel/render/modelentity.h"
#include "cxkernel/flow/cxmodel.h"
#include "cxkernel/render/printerentity.h"

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
	protected:
		void process(cxkernel::ModelNDataPtr data) override;

	protected:
		QList<CXModelPtr> m_models;
		PrinterEntity* m_printer;
	};
}
#endif // CXKERNEL_SIMULATIONFLOW_1684896500824_H