#ifndef _PRINTERENTITY_USE_1588651416007_H
#define _PRINTERENTITY_USE_1588651416007_H
#include "cxkernel/cxkernelinterface.h"
#include "cxkernel/data/header.h"

#include "qtuser3d/entity/boxentity.h"
#include "qtuser3d/entity/printergrid.h"
#include "qtuser3d/entity/axisentity.h"

namespace cxkernel
{
	class BoxEntity;
	class CXKERNEL_API PrinterEntity : public Qt3DCore::QEntity
	{
	public:
		PrinterEntity(Qt3DCore::QNode* parent = nullptr);
		virtual ~PrinterEntity();

		void updateSize(const trimesh::box& box);
	protected:
		BoxEntity* m_boxEntity;
		//qtuser_3d::PrinterGrid* m_printerGrid;
	};
}

#endif // _PRINTERENTITY_USE_1588651416007_H
