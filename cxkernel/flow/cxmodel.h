#ifndef CXKERNEL_CXMODEL_1684898814122_H
#define CXKERNEL_CXMODEL_1684898814122_H
#include "cxkernel/render/modelentity.h"
#include "cxkernel/data/modelndata.h"

namespace cxkernel
{
	class CXKERNEL_API CXModel : public QObject
	{
	public:
		CXModel(ModelEntity* entity, QObject* parent = nullptr);
		virtual ~CXModel();

		void setData(ModelNDataPtr data);
		ModelNDataPtr data();

		void offset(const trimesh::vec3& offset);
		void setPosition(const trimesh::vec3& position);
		void setRotate(const trimesh::quaternion& rotate);
		trimesh::fxform matrix();
	protected:
		void updateMatrix();
	protected:
		ModelEntity* m_entity;
		ModelNDataPtr m_data;

		trimesh::vec3 m_position;
		trimesh::quaternion m_rotate;
		trimesh::fxform m_xf;
	};

	typedef QSharedPointer<CXModel> CXModelPtr;
}

#endif // CXKERNEL_CXMODEL_1684898814122_H