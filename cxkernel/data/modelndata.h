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

	class CXKERNEL_API NestData
	{
	public:
		NestData();
		virtual ~NestData();

		void copyData(const NestData* nd);
		void setNestRotation(double angle);
		double getNestRotation();

		void calculateXYConvex(TriMeshPtr hull, const trimesh::fxform& rxf = trimesh::fxform::identity(),
			const trimesh::vec3& scale = trimesh::vec3(1.0f, 1.0f, 1.0f));

		void setDirty(bool dirty);
		bool dirty();

		std::vector<trimesh::vec3> path(bool simple = false);
		const std::vector<trimesh::vec3>& cPath(bool simple = false);
		std::vector<trimesh::vec3> concave_path(TriMeshPtr globalMesh);
	protected:
		TriMeshPtr convex;
		std::vector<trimesh::vec3> simples;

		double nestRotation;
		bool m_dirty;
	};

	typedef std::shared_ptr<NestData> NestDataPtr;
}

#endif // CXKERNEL_MODELNDATA_1681019989200_H