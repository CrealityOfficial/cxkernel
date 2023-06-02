#ifndef CXKERNEL_MODELNDATA_1681019989200_H
#define CXKERNEL_MODELNDATA_1681019989200_H
#include "cxkernel/cxkernelinterface.h"
#include "cxkernel/data/header.h"

#include "qtuser3d/geometry/attribute.h"
#include <Qt3DRender/QGeometry>

namespace cxkernel
{
	enum class ModelNDataType
	{
		mdt_none,
		mdt_file,
		mdt_cxbin,
		mdt_algrithm,
		mdt_project
	};

	struct ModelCreateInput
	{
		TriMeshPtr mesh;

		QString fileName;    // only for load
		QString name;
		QString description;
		ModelNDataType type = ModelNDataType::mdt_none;
	};

	class CXKERNEL_API ModelNData
	{
	public:
		ModelNData();
		~ModelNData();

		int primitiveNum();
		Qt3DRender::QGeometry* createGeometry();
		void updateRenderData();
		void updateRenderDataForced();
		trimesh::box3 calculateBox(const trimesh::fxform& matrix = trimesh::fxform::identity());
		trimesh::box3 localBox();
		float localZ();

		void convex(const trimesh::fxform& matrix, std::vector<trimesh::vec3>& datas);
		bool traitTriangle(int faceID, std::vector<trimesh::vec3>& position, const trimesh::fxform& matrix, bool offset = false);
		TriMeshPtr createGlobalMesh(const trimesh::fxform& matrix);

		TriMeshPtr mesh;
		TriMeshPtr hull;
		qtuser_3d::GeometryData renderData;

		trimesh::vec3 offset;
		ModelCreateInput input;
	};

	typedef std::shared_ptr<ModelNData> ModelNDataPtr;

	class ModelNDataProcessor
	{
	public:
		virtual ~ModelNDataProcessor() {}
		virtual void process(ModelNDataPtr data) = 0;
	};

	struct ModelNDataCreateParam
	{
		bool dumplicate = true;
		bool toCenter = true;
	};
	
	CXKERNEL_API ModelNDataPtr createModelNData(ModelCreateInput input,
													   ccglobal::Tracer* tracer = nullptr,
													   const ModelNDataCreateParam& param = ModelNDataCreateParam()
													   );
}

#endif // CXKERNEL_MODELNDATA_1681019989200_H