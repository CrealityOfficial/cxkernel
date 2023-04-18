#include "boxentity.h"

#include "qcxutil/trimesh2/renderprimitive.h"

namespace cxkernel
{
	BoxEntity::BoxEntity(Qt3DCore::QNode* parent)
		: XEntity(parent)
	{

	}

	BoxEntity::~BoxEntity()
	{

	}

	void BoxEntity::updateSize(const trimesh::box& box)
	{
		setGeometry(qcxutil::createCubeLines(box));
	}
}