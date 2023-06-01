#include "printerentity.h"

#include "qcxutil/trimesh2/conv.h"

namespace cxkernel
{
	PrinterEntity::PrinterEntity(Qt3DCore::QNode* parent)
		: QEntity(parent)
	{
		m_boxEntity = new PureEntity(this);
		//QVector4D greyColor = QVector4D(0.309804f, 0.313725f, 0.325490f, 1.0f);
		//m_printerGrid = new qtuser_3d::PrinterGrid(this);
		//m_printerGrid->setLineColor(greyColor);
		//m1.translate(0.0f, 0.0f, -0.05f);
		//m_printerGrid->setPose(m1);
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
