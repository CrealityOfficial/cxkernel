#ifndef _PRINTERENTITY_USE_1588651416007_H
#define _PRINTERENTITY_USE_1588651416007_H
#include "cxkernel/cxkernelinterface.h"
#include "cxkernel/data/header.h"

#include "cxkernel/render/pureentity.h"

namespace cxkernel
{
	class CXKERNEL_API PrinterEntity : public Qt3DCore::QEntity
	{
	public:
		PrinterEntity(Qt3DCore::QNode* parent = nullptr);
		virtual ~PrinterEntity();

		void updateSize(const trimesh::box& box);
		trimesh::box3 boundingBox();
	protected:
		trimesh::box3 m_bounding;
		cxkernel::PureEntity* m_boxEntity;
		//qtuser_3d::PrinterGrid* m_printerGrid;
	};
}

#endif // _PRINTERENTITY_USE_1588651416007_H
