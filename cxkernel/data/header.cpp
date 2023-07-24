#include "header.h"

#include "cxbin/load.h"
#include "stringutil/util.h"
#include "mmesh/trimesh/trimeshutil.h"

namespace cxkernel
{
	TriMeshPtr loadFromFile(const QString& fileName)
	{
		std::wstring strWname = fileName.toStdWString();
		std::string strname = stringutil::wstring2string(strWname);
		TriMeshPtr mesh(cxbin::loadAll(strname, nullptr));

		mmesh::dumplicateMesh(mesh.get());
		return mesh;
	}
}