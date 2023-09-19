#ifndef CXKERNEL_TRIMESHSERIAL_1691656350835_H
#define CXKERNEL_TRIMESHSERIAL_1691656350835_H
#include "cxkernel/data/modelndata.h"
#include "ccglobal/serial.h"
#include "trimesh2/TriMesh.h"

namespace cxkernel
{
	typedef std::vector<trimesh::vec3> CXNDPolygon;
	typedef std::vector<CXNDPolygon> CXNDPolygons;

	CXKERNEL_API trimesh::TriMesh* loadTrimesh(std::fstream& in);
	CXKERNEL_API void saveTrimesh(std::fstream& out, trimesh::TriMesh* mesh);

	CXKERNEL_API bool loadTrimesh(std::fstream& in, trimesh::TriMesh& mesh);
	CXKERNEL_API void saveTrimesh(std::fstream& out, const trimesh::TriMesh& mesh);

	class CXKERNEL_API CXNDPolygonsWrapper : public ccglobal::Serializeable
	{
	public:
		CXNDPolygonsWrapper();
		~CXNDPolygonsWrapper();

		CXNDPolygons polys;

		int version() override;
		bool save(std::fstream& out, ccglobal::Tracer* tracer) override;
		bool load(std::fstream& in, int ver, ccglobal::Tracer* tracer) override;
	};

	CXKERNEL_API void loadPolys(std::fstream& in, CXNDPolygons& polys);
	CXKERNEL_API void savePolys(std::fstream& out, const CXNDPolygons& polys);
}

#endif // CXKERNEL_TRIMESHSERIAL_1691656350835_H