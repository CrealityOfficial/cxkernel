#ifndef CXKERNEL_BOXENTITY_1679997376180_H
#define CXKERNEL_BOXENTITY_1679997376180_H
#include "qtuser3d/prospective/xentity.h"

namespace cxkernel
{
	class BoxEntity : public qtuser_3d::XEntity
	{
	public:
		BoxEntity(QNode* parent = nullptr);
		virtual ~BoxEntity();
	};
}

#endif // CXKERNEL_BOXENTITY_1679997376180_H