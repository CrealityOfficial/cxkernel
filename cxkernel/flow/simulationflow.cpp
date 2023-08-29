#include "simulationflow.h"
#include "qtuser3d/camera/cameracontroller.h"

#include "qcxutil/trimesh2/conv.h"
#include "cxkernel/utils/layoutjob.h"
#include "cxkernel/utils/anonymousjob.h"
#include "qtusercore/module/progressortracer.h"
#include "qtuser3d/camera/screencamera.h"

#include "cxkernel/interface/jobsinterface.h"
#include "cxkernel/data/modelndataserial.h"
#include "cxkernel/utils/utils.h"

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

	void SimulationFlow::home()
	{
		viewPrinter();
	}

	void SimulationFlow::viewPrinter()
	{
		m_cameraController->home(qcxutil::triBox2Box3D(m_printer->boundingBox()));
	}

	void SimulationFlow::viewModels(bool visible)
	{
		for (CXModelPtr model : m_models)
			model->setVisible(visible);
	}

	void SimulationFlow::renderMode(int index, int mode)
	{
		CXModelPtr m = model(index);

		if (m)
			setModelRenderEffectMode(m, (cxkernel::RenderEffectMode)mode);
	}

	void SimulationFlow::loadMeshFile(const QString& fileName, bool raw)
	{
		TriMeshPtr mesh = cxkernel::loadFromFile(fileName);

		if (!mesh)
			return;

		if (raw)
			addRawMesh(mesh);
		else
			addMesh(mesh);
	}

	void SimulationFlow::saveQuickFile(const QString& fileName, int index)
	{
		CXModelPtr m = model(index);
		if (!m)
			return;

		ModelNDataSerial serial;
		serial.setData(m->data());
		serial.save(fileName, nullptr);
	}

	void SimulationFlow::loadQuickFile(const QString& fileName)
	{
		ModelNDataSerial serial;
		serial.load(fileName, nullptr);

		ModelNDataPtr data = serial.getData();
		pushModel(data, false);
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

	void SimulationFlow::copyMesh(TriMeshPtr mesh)
	{
		if (!mesh)
			return;

		TriMeshPtr newMesh(new trimesh::TriMesh());
		*newMesh = *mesh;

		addMesh(newMesh);
	}

	void SimulationFlow::addRawMesh(TriMeshPtr mesh, bool toCenter)
	{
		cxkernel::ModelNDataCreateParam param;
		param.dumplicate = true;
		param.toCenter = toCenter;
		addMesh(mesh, param);
	}

	void SimulationFlow::addMesh(TriMeshPtr mesh, const ModelNDataCreateParam& param)
	{
		if (!mesh)
			return;

		cxkernel::ModelCreateInput input;
		input.mesh = mesh;

		cxkernel::ModelNDataPtr data = cxkernel::createModelNData(input, nullptr, param);
		pushModel(data, param.toCenter);
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

		m_models.push_back(model);
		onCXModelCreated(model);

		if (lowerZ)
			insert(model);

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

	void SimulationFlow::_lines(qtuser_3d::XEntity* entity, const std::vector<std::vector<trimesh::vec3>>& lines)
	{
		std::vector<trimesh::vec3> ls;
		for (const std::vector<trimesh::vec3>& l : lines)
			ls.insert(ls.end(), l.begin(), l.end());
		_lines(entity, ls);
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

	void SimulationFlow::_points(const QString& name, const std::vector<trimesh::vec3>& points)
	{
		qtuser_3d::XEntity* entity = _find(name);
		_points(entity, points);
	}

	void SimulationFlow::_points(qtuser_3d::XEntity* entity, const std::vector<trimesh::vec3>& points)
	{
		if (entity)
			entity->setGeometry(qcxutil::createPoints(points), Qt3DRender::QGeometryRenderer::Points);
	}

	void SimulationFlow::_transform(const QString& name, const QMatrix4x4& m)
	{
		qtuser_3d::XEntity* entity = _find(name);
		_transform(entity, m);
	}

	void SimulationFlow::_transform(qtuser_3d::XEntity* entity, const QMatrix4x4& m)
	{
		if (entity)
			entity->setModelMatrix(m);
	}

	void SimulationFlow::_bind(const QString& name, CXModelPtr model)
	{
		qtuser_3d::XEntity* entity = _find(name);
		_bind(entity, model);
	}

	void SimulationFlow::_bind(qtuser_3d::XEntity* entity, CXModelPtr model)
	{
		if (entity && model)
			entity->setParent(model->entity());
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

	qtuser_3d::Pickable* SimulationFlow::pickPickable(const QPoint& point, int* primitiveID)
	{
		return m_selector->check(point, primitiveID);
	}

	CXModelPtr SimulationFlow::checkPickModel(const QPoint& point, trimesh::vec3& position, trimesh::vec3& normal, int* primitiveID)
	{
		int _primitiveID = -1;
		CXModelPtr model = pick(point, &_primitiveID);
		if (model)
		{
			model->rayCheck(_primitiveID, visRay(point), position, &normal);
		}
		if (primitiveID)
		{
			*primitiveID = _primitiveID;
		}
		return model;
	}

	cxnd::Ray SimulationFlow::visRay(const QPoint& point)
	{
		qtuser_3d::Ray _ray = m_screenCamera->screenRay(point);

		cxnd::Ray ray;
		ray.start = qcxutil::qVector3D2Vec3(_ray.start);
		ray.dir = qcxutil::qVector3D2Vec3(_ray.dir);
		return ray;
	}

	void SimulationFlow::setModelRenderEffectMode(CXModelPtr model, RenderEffectMode mode)
	{
		if (model)
		{
			ModelPhongEffect* effect = model->entity()->mEffect();
			effect->setRenderEffectMode(mode);
		}
	}

	void SimulationFlow::updateModelColor(CXModelPtr model, const QByteArray& bytes)
	{
		if (!model)
			return;

		model->entity()->mEffect()->useColor(true);
		model->entity()->updateAttribute(2, bytes);
	}

	void SimulationFlow::circleDirectory(const QString& directory, circleLoadFunc func)
	{
		cxkernel::circleDirectory(directory, func);
	}

	void SimulationFlow::ansycBatch(const QString& directory, circleLoadFunc func)
	{
		cxkernel::ansycBatch(directory, func);
	}

	void SimulationFlow::insert(CXModelPtr model)
	{
		if (!model)
			return;

		QList<cxkernel::CXModelPtr> _models = models();
		QList<cxkernel::CXModelPtr> __models;
		for (cxkernel::CXModelPtr m : _models)
			if (m != model)
				__models.push_back(m);

		LayoutJob* job = new LayoutJob(this);
		job->setBounding(m_printer->boundingBox());
		job->setModels(__models);
		job->setInsert(model);

		cxkernel::executeJob(job);
	}

	void SimulationFlow::runAnonymous(anonymous_work_func workFunc, anonymous_func successFunc)
	{
		cxkernel::runAnonymous(workFunc, successFunc);
	}

	void SimulationFlow::_requestUpdate()
	{
		m_selector->updateFaceBases();
		requestCapture(true);
	}
}