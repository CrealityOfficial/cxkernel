#include "simpletriangleentity.h"

namespace cxkernel
{
	SimpleTriangleEntity::SimpleTriangleEntity(Qt3DCore::QNode* parent)
		: PureEntity(parent)
	{
		setParameter("color", QVector4D(0.6f, 0.6f, 0.0f, 1.0f));
	}

	SimpleTriangleEntity::~SimpleTriangleEntity()
	{

	}

	void SimpleTriangleEntity::setTriangle(const trimesh::vec3& v1, const trimesh::vec3& v2, const trimesh::vec3& v3)
	{
		setGeometry(qcxutil::createSimpleTriangle(v1, v2, v3));
	}
}