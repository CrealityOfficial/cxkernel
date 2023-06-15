#include "cxmodel.h"
#include "qcxutil/trimesh2/conv.h"
#include "mmesh/trimesh/algrithm3d.h"

namespace cxkernel
{
	CXModel::CXModel(ModelEntity* entity, QObject* parent)
		: QObject(parent)
		, m_entity(entity)
	{

	}

	CXModel::~CXModel()
	{
		delete m_entity;
	}

	void CXModel::setData(ModelNDataPtr data)
	{
		m_data = data;
		
		m_entity->setGeometry(m_data ? m_data->createGeometry() : nullptr);
	}

	ModelNDataPtr CXModel::data()
	{
		return m_data;
	}

	qcxutil::NestDataPtr CXModel::nestData()
	{
		if (!m_nest)
			m_nest.reset(new qcxutil::NestData());

		return m_nest;
	}

	void CXModel::offset(const trimesh::vec3& offset)
	{
		m_position += offset;
		updateMatrix();
	}

	void CXModel::setPosition(const trimesh::vec3& position)
	{
		m_position = position;
		updateMatrix();
	}

	trimesh::vec3 CXModel::position()
	{
		return m_position;
	}

	void CXModel::setRotate(const trimesh::quaternion& rotate)
	{
		m_rotate = rotate;
		updateMatrix();
	}

	trimesh::quaternion CXModel::rotate()
	{
		return m_rotate;
	}

	trimesh::fxform CXModel::matrix()
	{
		return m_xf;
	}

	void CXModel::resetNestRotation()
	{
		nestData()->setNestRotation(rotate());
	}

	trimesh::quaternion CXModel::nestRotation()
	{
		return nestData()->nestRotation();
	}

	trimesh::box3 CXModel::globalBox()
	{
		return m_data->calculateBox(m_xf);
	}

	std::vector<trimesh::vec3> CXModel::outline_path()
	{
		return nestData()->path(m_data->hull);
	}

	std::vector<trimesh::vec3> CXModel::debug_path(bool origin)
	{
		std::vector<trimesh::vec3> paths = outline_path();

		trimesh::vec3 pos = position();
		trimesh::fxform xf = trimesh::fxform::trans(trimesh::vec3(pos.x, pos.y, 0.0f));
		if (!origin)
			xf = xf * trimesh::fromQuaterian(nestData()->nestRotation());

		mmesh::applyMatrix2Points(paths, xf);
		return paths;
	}

	std::vector<trimesh::vec3> CXModel::concave_path()
	{
		TriMeshPtr mesh = createGlobalMesh();
		return nestData()->concave_path(mesh);
	}

	TriMeshPtr CXModel::createGlobalMesh()
	{
		return m_data->createGlobalMesh(m_xf);
	}

	void CXModel::setVisible(bool visible)
	{
		m_entity->setEnabled(visible);
	}

	void CXModel::updateMatrix()
	{
		m_xf = trimesh::fxform::trans(m_position) * trimesh::fromQuaterian(m_rotate);

		m_entity->setPose(qcxutil::xform2QMatrix(m_xf));
	}
}