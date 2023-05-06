#ifndef CXKERNEL_SIMPLETRIANGLEENTITY_1683343013360_H
#define CXKERNEL_SIMPLETRIANGLEENTITY_1683343013360_H
#include "cxkernel/render/pureentity.h"
#include "cxkernel/data/header.h"

namespace cxkernel
{
	class CXKERNEL_API SimpleTriangleEntity : public cxkernel::PureEntity
	{
	public:
		SimpleTriangleEntity(Qt3DCore::QNode* parent = nullptr);
		virtual ~SimpleTriangleEntity();

		void setTriangle(const trimesh::vec3& v1, const trimesh::vec3& v2, const trimesh::vec3& v3);
	};
}

#endif // CXKERNEL_SIMPLETRIANGLEENTITY_1683343013360_H