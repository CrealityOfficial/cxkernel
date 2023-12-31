#ifndef CXKERNEL_CXMODEL_1684898814122_H
#define CXKERNEL_CXMODEL_1684898814122_H
#include "cxkernel/render/modelentity.h"
#include "cxkernel/data/modelndata.h"
#include "qtuser3d/module/pickable.h"
#include "qcxutil/util/nestdata.h"

namespace cxkernel
{
	class CXKERNEL_API CXModel : public qtuser_3d::Pickable
	{
	public:
		CXModel(ModelEntity* entity, QObject* parent = nullptr);
		virtual ~CXModel();

		void setData(ModelNDataPtr data);
		ModelNDataPtr data();

		void offset(const trimesh::vec3& offset);
		void setPosition(const trimesh::vec3& position);
		trimesh::vec3 position();
		void setRotate(const trimesh::quaternion& rotate);
		trimesh::quaternion rotate();

		trimesh::fxform matrix();
		trimesh::box3 globalBox();

		trimesh::quaternion nestRotation();
		void resetNestRotation();
		void setNestRotation(const trimesh::quaternion& _rotation);
		void dirtyNestData();

		std::vector<trimesh::vec3> outline_path(bool global = false, bool debug = false);
		std::vector<trimesh::vec3> concave_path();

		TriMeshPtr createGlobalMesh();

		void setVisible(bool visible) override;
		ModelEntity* entity();
	protected:
		void updateMatrix();
		qcxutil::NestDataPtr nestData();

		int primitiveNum() override;   // 0
	protected:
		ModelEntity* m_entity;
		ModelNDataPtr m_data;
		qcxutil::NestDataPtr m_nest;

		trimesh::vec3 m_position;
		trimesh::quaternion m_rotate;
		trimesh::fxform m_xf;
	};

	typedef QSharedPointer<CXModel> CXModelPtr;
}

#endif // CXKERNEL_CXMODEL_1684898814122_H