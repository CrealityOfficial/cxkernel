#include "simulationflow.h"
#include "qtuser3d/camera/cameracontroller.h"

#include "qcxutil/trimesh2/conv.h"

namespace cxkernel
{
	SimulationFlow::SimulationFlow(const SimulationConfig& config, Qt3DCore::QNode* parent)
		:XRenderGraph(parent)
		, m_config(config)
	{
		m_printer = new PrinterEntity(this);
		m_printer->setEnabled(m_config.showPrinter);
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

	void SimulationFlow::pushModel(ModelNDataPtr data)
	{
		if (!data)
			return;

		CXModel* model = new CXModel(new ModelEntity(this));
		model->setData(data);

		trimesh::box3 box = data->calculateBox();
		model->offset(trimesh::vec3(0.0f, 0.0f, -box.min.z));

		m_models.push_back(CXModelPtr(model));
	}

	void SimulationFlow::pushModels(const QList<ModelNDataPtr>& datas)
	{
		for (ModelNDataPtr data : datas)
			pushModel(data);
	}

	void SimulationFlow::clearModels()
	{
		m_models.clear();
	}

	void SimulationFlow::process(cxkernel::ModelNDataPtr data)
	{
		onModelLoaded(data);
		pushModel(data);
	}

	void SimulationFlow::onModelLoaded(ModelNDataPtr data)
	{

	}
}