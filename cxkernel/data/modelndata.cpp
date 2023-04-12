#include "modelndata.h"
#include "qcxutil/trimesh2/q3drender.h"
#include "qtuser3d/geometry/geometrycreatehelper.h"
#include "qhullWrapper/hull/meshconvex.h"
#include "mmesh/trimesh/trimeshutil.h"

#include "qtusercore/module/progressortracer.h"

namespace cxkernel
{
	ModelNData::ModelNData()
	{

	}

	ModelNData::~ModelNData()
	{

	}

	int ModelNData::primitiveNum()
	{
		return mesh ? (int)mesh->faces.size() : 0;
	}

	trimesh::box3 ModelNData::calculateBox(const trimesh::fxform& matrix)
	{
		trimesh::box3 b;

		if (hull)
		{
			for (const trimesh::vec3& v : hull->vertices)
				b += matrix * v;
		}
		else if (mesh)
		{
			if (mesh->flags.size() == mesh->vertices.size())
			{
				for (int i : mesh->flags)
					b += matrix * mesh->vertices.at(i);
			}
			else
			{
				int size = (int)mesh->vertices.size();
				for (int i = 0; i < size; ++i)
				{
					trimesh::vec3 v = mesh->vertices.at(i);
					b += matrix * v;
				}
			}
		}

		return b;
	}

	trimesh::box3 ModelNData::localBox()
	{
		trimesh::box3 b;
		if (mesh)
			b = mesh->bbox;
		return b;
	}

	void ModelNData::convex(const trimesh::fxform& matrix, std::vector<trimesh::vec3>& datas)
	{
		std::vector<trimesh::vec2> hullPoints2D;
		if (hull)
		{
			int size = (int)hull->vertices.size();
			hullPoints2D.reserve(size);
			for (const trimesh::vec3& v : hull->vertices)
			{
				trimesh::vec3 p = matrix * v;

				hullPoints2D.emplace_back(trimesh::vec2(p.x, p.y));
			}
		}
		else if (mesh->flags.size() > 0)
		{
			int size = (int)mesh->vertices.size();
			for (int i : mesh->flags)
			{
				if (i >= 0 && i < size)
				{
					trimesh::vec3 p = matrix * mesh->vertices.at(i);
					hullPoints2D.emplace_back(trimesh::vec2(p.x, p.y));
				}
			}
		}

		if (hullPoints2D.size() == 0)
			return;

		trimesh::TriMesh* m = qhullWrapper::convex2DPolygon((const float*)hullPoints2D.data(), hullPoints2D.size());
		if (!m)
			return;

		datas.clear();
		for (const trimesh::vec3& p : m->vertices)
			datas.emplace_back(trimesh::vec3(p.x, p.y, 0.0f));

		delete m;
	}

	ModelNDataPtr createModelNData(ModelCreateInput input, ccglobal::Tracer* tracer,
		const ModelNDataCreateParam& param)
	{
		if (input.mesh)
		{
			if (tracer)
				tracer->resetProgressScope();

			input.mesh->normals.clear();

			if(param.dumplicate)
				mmesh::dumplicateMesh(input.mesh.get(), tracer);

			input.mesh->clear_bbox();
			input.mesh->need_bbox();

			if(param.toCenter)
				mmesh::moveTrimesh2Center(input.mesh.get(), false);

			ModelNDataPtr data(new ModelNData());
			data->mesh = input.mesh;
			data->input = input;
			data->hull.reset(qhullWrapper::convex_hull_3d(input.mesh.get()));
			qcxutil::trimesh2AttributeShade(input.mesh.get(), data->positionAttribute, data->normalAttribute);

			return data;
		}

		return nullptr;
	}
}