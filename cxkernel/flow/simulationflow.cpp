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

	QList<CXModelPtr> SimulationFlow::models()
	{
		return m_models;
	}

	void SimulationFlow::showPrinter(bool show)
	{
		m_printer->setEnabled(show);
	}

	CXModelPtr SimulationFlow::model(int index)
	{
		if (index >= 0 && index < m_models.size())
			return m_models.at(index);

		return nullptr;
	}

	void SimulationFlow::pushModel(ModelNDataPtr data, bool lowerZ)
	{
		if (!data)
			return;

		CXModelPtr model(new CXModel(new ModelEntity(this)));
		model->setData(data);

		if (lowerZ)
		{
			trimesh::box3 box = data->calculateBox();
			model->offset(trimesh::vec3(0.0f, 0.0f, -box.min.z));
		}

		onCXModelCreated(model);
		m_models.push_back(model);
	}

	void SimulationFlow::pushModels(const QList<ModelNDataPtr>& datas, bool lowerZ)
	{
		for (ModelNDataPtr data : datas)
			pushModel(data, lowerZ);
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

	void SimulationFlow::onCXModelCreated(CXModelPtr model)
	{

	}
}