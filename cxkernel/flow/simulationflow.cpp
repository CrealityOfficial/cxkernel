#include "simulationflow.h"
#include "qtuser3d/camera/cameracontroller.h"

#include "qcxutil/trimesh2/conv.h"
#include <QtCore/QDir>

namespace cxkernel
{
	SimulationFlow::SimulationFlow(Qt3DCore::QNode* parent)
		:XRenderGraph(parent)
	{
		m_printer = new PrinterEntity(this);
		m_picker = new qtuser_3d::ColorPicker(m_cameraSelector);
		m_picker->useSelfTarget();
		connect(m_cameraController, SIGNAL(signalViewChanged(bool)), this, SLOT(requestCapture(bool)));

		m_selector = new qtuser_3d::Selector(this);
		m_selector->setPickerSource(m_picker);
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

	void SimulationFlow::viewBox(const trimesh::box3& box)
	{
		m_cameraController->home(qcxutil::triBox2Box3D(box));
	}

	void SimulationFlow::viewPrinter()
	{
		m_cameraController->home(qcxutil::triBox2Box3D(m_printer->boundingBox()));
	}

	void SimulationFlow::requestCapture(bool capture)
	{
		if (capture)
			m_picker->requestCapture();
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

		m_selector->addPickable(model.get());
		requestCapture(true);
	}

	void SimulationFlow::pushModels(const QList<ModelNDataPtr>& datas, bool lowerZ)
	{
		for (ModelNDataPtr data : datas)
			pushModel(data, lowerZ);
	}

	void SimulationFlow::clearModels()
	{
		for (CXModelPtr model : m_models)
			m_selector->removePickable(model.get());
		m_models.clear();
	}

	void SimulationFlow::process(cxkernel::ModelNDataPtr data)
	{
		onModelLoaded(data);
		pushModel(data);
	}

	void SimulationFlow::onResize(const QSize& size)
	{
		m_picker->resize(size);
	}

	void SimulationFlow::onModelLoaded(ModelNDataPtr data)
	{

	}

	void SimulationFlow::onCXModelCreated(CXModelPtr model)
	{

	}

	void SimulationFlow::_add(const QString& name, qtuser_3d::XEntity* entity)
	{
		qtuser_3d::XEntity* en = _find(name);
		if (entity && !en)
		{
			entity->addPassFilter(0, "view");
			m_namedEntities.insert(name, entity);
		}
	}

	void SimulationFlow::_remove(const QString& name)
	{
		qtuser_3d::XEntity* entity = _find(name);
		m_namedEntities.remove(name);
		if (entity)
			delete entity;
	}

	qtuser_3d::XEntity* SimulationFlow::_find(const QString& name)
	{
		QMap<QString, qtuser_3d::XEntity*>::const_iterator it = m_namedEntities.find(name);
		if (it != m_namedEntities.end())
			return it.value();
		
		return nullptr;
	}

	void SimulationFlow::_lines(const QString& name, const std::vector<trimesh::vec3>& lines)
	{
		qtuser_3d::XEntity* entity = _find(name);
		_lines(entity, lines);
	}

	void SimulationFlow::_lines(qtuser_3d::XEntity* entity, const std::vector<trimesh::vec3>& lines)
	{
		if (entity)
			entity->setGeometry(qcxutil::createLinesGeometry(lines), Qt3DRender::QGeometryRenderer::Lines);
	}

	void SimulationFlow::_triangle(const QString& name, const std::vector<trimesh::vec3>& tris)
	{
		qtuser_3d::XEntity* entity = _find(name);
		_triangle(entity, tris);
	}

	void SimulationFlow::_triangle(qtuser_3d::XEntity* entity, const std::vector<trimesh::vec3>& tris)
	{
		if (entity)
			entity->setGeometry(qcxutil::createTriangles(tris), Qt3DRender::QGeometryRenderer::Triangles);
	}

	cxkernel::PureEntity* SimulationFlow::createPure(const QString& name)
	{
		cxkernel::PureEntity* entity = new cxkernel::PureEntity(this);
		_add(name, entity);
		return entity;
	}

	CXModelPtr SimulationFlow::pick(const QPoint& point, int* primitiveID)
	{
		qtuser_3d::Pickable* pickable = m_selector->check(point, primitiveID);

		for (CXModelPtr model : m_models)
		{
			if (model.get() == pickable)
				return model;
		}

		return nullptr;
	}

	void SimulationFlow::setModelRenderEffectMode(CXModelPtr model, RenderEffectMode mode)
	{
		if (model)
		{
			ModelPhongEffect* effect = model->entity()->mEffect();
			effect->setRenderEffectMode(mode);
		}
	}

	void SimulationFlow::circleDirectory(const QString& directory, circleLoadFunc func)
	{
		QList<QString> fileNames;

		QDir dir(directory);
		QList<QFileInfo> fileInfos = dir.entryInfoList(QStringList(), QDir::Files);

		for (const QFileInfo& fileInfo : fileInfos)
		{
			if (fileInfo.isFile())
				fileNames << fileInfo.absoluteFilePath();
		}

		for(const QString& fileName : fileNames)
			func(fileName);
	}
}