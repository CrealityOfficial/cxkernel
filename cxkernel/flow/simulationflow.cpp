#include "simulationflow.h"
#include "qtuser3d/camera/cameracontroller.h"

#include "qcxutil/trimesh2/conv.h"

namespace cxkernel
{
	SimulationFlow::SimulationFlow(Qt3DCore::QNode* parent)
		:XRenderGraph(parent)
	{
		m_printer = new PrinterEntity(this);
	}

	SimulationFlow::~SimulationFlow()
	{

	}

	void SimulationFlow::init()
	{
		initialize();

		trimesh::box3 box;
		box += trimesh::vec3();
		box += trimesh::vec3(400.0f, 400.0f, 400.0f);
		m_printer->updateSize(box);

		m_cameraController->home(qcxutil::triBox2Box3D(box));
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

	CXModelPtr SimulationFlow::model(int index)
	{
		if (index >= 0 && index < m_models.size())
			return m_models.at(index);

		return nullptr;
	}

	void SimulationFlow::process(cxkernel::ModelNDataPtr data)
	{
		CXModel* model = new CXModel(new ModelEntity(this));
		model->setData(data);
		m_models.push_back(CXModelPtr(model));
	}
}