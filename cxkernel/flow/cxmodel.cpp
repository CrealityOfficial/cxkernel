#include "cxmodel.h"
#include "qcxutil/trimesh2/conv.h"

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

	void CXModel::setRotate(const trimesh::quaternion& rotate)
	{
		m_rotate = rotate;
		updateMatrix();
	}

	trimesh::fxform CXModel::matrix()
	{
		return m_xf;
	}

	void CXModel::updateMatrix()
	{
		m_xf = trimesh::fxform::trans(m_position) * trimesh::fromQuaterian(m_rotate);

		m_entity->setPose(qcxutil::xform2QMatrix(m_xf));
	}
}