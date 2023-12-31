#include "printerentity.h"

#include "qcxutil/trimesh2/conv.h"

namespace cxkernel
{
	PrinterEntity::PrinterEntity(Qt3DCore::QNode* parent)
		: QEntity(parent)
	{
		m_boxEntity = new PureEntity(this);
		m_boxEntity->addPassFilter(0, "view");
	}

	PrinterEntity::~PrinterEntity()
	{
	}

	void PrinterEntity::updateSize(const trimesh::box& box)
	{
		m_bounding = box;
		m_boxEntity->setGeometry(qcxutil::createCubeLines(box), Qt3DRender::QGeometryRenderer::Lines);
		//qtuser_3d::Box3D qBox = qcxutil::triBox2Box3D(box);
		//m_boxEntity->updateGlobal(qBox, false);
		//m_printerGrid->updateBounding(qBox, 1);
	}

	trimesh::box3 PrinterEntity::boundingBox()
	{
		return m_bounding;
	}
}
