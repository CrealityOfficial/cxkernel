#ifndef CXKERNEL_MODELNDATA_1681019989200_H
#define CXKERNEL_MODELNDATA_1681019989200_H
#include "cxkernel/cxkernelinterface.h"
#include "cxkernel/data/attribute.h"
#include "cxkernel/data/header.h"
#include "qhullWrapper/hull/hullface.h"

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
		void updateRenderData();
		void updateRenderDataForced();
		void updateIndexRenderData();
		trimesh::box3 calculateBox(const trimesh::fxform& matrix = trimesh::fxform::identity());
		trimesh::box3 localBox();
		float localZ();

		void calculateFaces();
		void convex(const trimesh::fxform& matrix, std::vector<trimesh::vec3>& datas);
		bool traitTriangle(int faceID, std::vector<trimesh::vec3>& position, const trimesh::fxform& matrix, bool offset = false);
		TriMeshPtr createGlobalMesh(const trimesh::fxform& matrix);

		TriMeshPtr mesh;
		TriMeshPtr hull;
		cxkernel::GeometryData renderData;
		std::vector<qhullWrapper::HullFace> faces;

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
		bool indexRender = false;
	};
	
	CXKERNEL_API ModelNDataPtr createModelNData(ModelCreateInput input,
													   ccglobal::Tracer* tracer = nullptr,
													   const ModelNDataCreateParam& param = ModelNDataCreateParam()
													   );
}

#endif // CXKERNEL_MODELNDATA_1681019989200_H