#ifndef CXKERNEL_MESHDATA_1681019989200_H
#define CXKERNEL_MESHDATA_1681019989200_H
#include "cxkernel/cxkernelinterface.h"
#include "cxkernel/data/attribute.h"
#include "cxkernel/data/header.h"
#include "modelndata.h"

namespace cxkernel
{
	class CXKERNEL_API MeshData 
	{
	public:
		MeshData(trimesh::TriMesh* mesh, bool toCenter = true);
		MeshData();
		
		void setMesh(trimesh::TriMesh* mesh, bool toCenter = true);

		trimesh::box3 calculateBox(const trimesh::fxform& matrix = trimesh::fxform::identity());

		trimesh::box3 localBox();

		float localZ();

		void calculateFaces();

		void resetHull();

		void adaptSmallBox(const trimesh::box3& box);

		void adaptBigBox(const trimesh::box3& box);

		void convex(const trimesh::fxform& matrix, std::vector<trimesh::vec3>& datas);

		bool traitTriangle(int faceID, std::vector<trimesh::vec3>& position, const trimesh::fxform& matrix, bool _offset);

		TriMeshPtr createGlobalMesh(const trimesh::fxform& matrix);

		bool traitTriangleEx(int faceID, std::vector<trimesh::vec3>& position, trimesh::vec3& normal, const trimesh::fxform& matrix, float offsetValue, bool _offset);

	public:
		TriMeshPtr mesh;
		TriMeshPtr hull;
		trimesh::vec3 offset;
		std::vector<cxkernel::KernelHullFace> faces;

	};

}

#endif // CXKERNEL_MESHDATA_1681019989200_H