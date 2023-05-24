#ifndef CXKERNEL_SIMULATIONFLOW_1684896500824_H
#define CXKERNEL_SIMULATIONFLOW_1684896500824_H
#include "qtuser3d/framegraph/xrendergraph.h"
#include "cxkernel/data/modelndata.h"
#include "cxkernel/render/modelentity.h"

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
	protected:
		void process(cxkernel::ModelNDataPtr data) override;

	protected:
	};
}
#endif // CXKERNEL_SIMULATIONFLOW_1684896500824_H