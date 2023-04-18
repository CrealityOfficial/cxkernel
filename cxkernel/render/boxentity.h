#ifndef CXKERNEL_BOXENTITY_1681806761342_H
#define CXKERNEL_BOXENTITY_1681806761342_H
#include "cxkernel/cxkernelinterface.h"
#include "qtuser3d/refactor/xentity.h"
#include "trimesh2/Box.h"

namespace cxkernel
{
	class CXKERNEL_API BoxEntity : public qtuser_3d::XEntity
	{
	public:
		BoxEntity(Qt3DCore::QNode* parent = nullptr);
		virtual ~BoxEntity();

		void updateSize(const trimesh::box& box);
	};
}

#endif // CXKERNEL_BOXENTITY_1681806761342_H