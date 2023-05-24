#include "simulationflow.h"

namespace cxkernel
{
	SimulationFlow::SimulationFlow(Qt3DCore::QNode* parent)
		:XRenderGraph(parent)
	{

	}

	SimulationFlow::~SimulationFlow()
	{

	}

	void SimulationFlow::init()
	{
		initialize();
	}

	void SimulationFlow::uninit()
	{
		unInitialize();
	}

	void SimulationFlow::initialize()
	{

	}

	void SimulationFlow::unInitialize()
	{

	}

	void SimulationFlow::process(cxkernel::ModelNDataPtr data)
	{

	}
}