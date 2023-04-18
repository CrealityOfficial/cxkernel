#include "boxentity.h"

#include "qcxutil/trimesh2/renderprimitive.h"
#include "cxkernel/render/purexeffect.h"

namespace cxkernel
{
	BoxEntity::BoxEntity(Qt3DCore::QNode* parent)
		: XEntity(parent)
	{
		setEffect(new PureXEffect());
	}

	BoxEntity::~BoxEntity()
	{

	}

	void BoxEntity::updateSize(const trimesh::box& box)
	{
		setGeometry(qcxutil::createCubeLines(box), Qt3DRender::QGeometryRenderer::Lines);
	}
}