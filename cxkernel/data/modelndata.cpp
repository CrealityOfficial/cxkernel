#include "modelndata.h"
#include "qcxutil/trimesh2/q3drender.h"
#include "qcxutil/trimesh2/trimesh2qgeometryrenderer.h"
#include "qtuser3d/geometry/geometrycreatehelper.h"
#include "qhullWrapper/hull/meshconvex.h"
#include "mmesh/trimesh/trimeshutil.h"
#include "mmesh/util/checker.h"

#include "qtusercore/module/progressortracer.h"
#include <QtCore/QDebug>

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

	Qt3DRender::QGeometry* ModelNData::createGeometry()
	{
		updateRenderData();
		return qtuser_3d::GeometryCreateHelper::create(renderData, nullptr);
	}

	void ModelNData::updateRenderData()
	{
		if (mesh && ((int)mesh->faces.size() != renderData.fcount))
			qcxutil::generateGeometryDataFromMesh(mesh.get(), renderData);
	}

	void ModelNData::updateRenderDataForced()
	{
		qcxutil::generateGeometryDataFromMesh(mesh.get(), renderData);
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

	float ModelNData::localZ()
	{
		trimesh::box3 b = localBox();
		return b.min.z - offset.z;
	}

	void ModelNData::calculateFaces()
	{
		if (faces.size() == 0)
		{
			qhullWrapper::hullFacesFromConvexMesh(hull.get(), faces);
		}
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

	bool ModelNData::traitTriangle(int faceID, std::vector<trimesh::vec3>& position, const trimesh::fxform& matrix, bool _offset)
	{
		if (!mesh || faceID < 0 || faceID >= (int)mesh->faces.size())
			return false;

		const trimesh::TriMesh::Face& face = mesh->faces.at(faceID);
		position.clear();
		position.push_back(matrix * mesh->vertices.at(face.x));
		position.push_back(matrix * mesh->vertices.at(face.y));
		position.push_back(matrix * mesh->vertices.at(face.z));

		if (_offset)
		{
			trimesh::vec3 n = trimesh::trinorm(position.at(0), position.at(1), position.at(2));
			trimesh::normalize(n);

			position.at(0) += 0.1f * n;
			position.at(1) += 0.1f * n;
			position.at(2) += 0.1f * n;
		}
		return true;
	}

	TriMeshPtr ModelNData::createGlobalMesh(const trimesh::fxform& matrix)
	{
		if (!mesh)
			return nullptr;

		trimesh::TriMesh* newMesh = new trimesh::TriMesh();
		*newMesh = *mesh;
		trimesh::apply_xform(newMesh, trimesh::xform(matrix));
		return TriMeshPtr(newMesh);
	}

	ModelNDataPtr createModelNData(ModelCreateInput input, ccglobal::Tracer* tracer,
		const ModelNDataCreateParam& param)
	{
		if (input.mesh)
		{
			if (tracer)
				tracer->resetProgressScope();

			input.mesh->normals.clear();

			bool processResult = true;
			if (param.dumplicate)
			{
				processResult = mmesh::dumplicateMesh(input.mesh.get(), tracer);
				if (!processResult)
				{
					return nullptr;
				}
			}

			bool have = mmesh::checkDegenerateFace(input.mesh.get(), true);
			if (have)
			{
				qDebug() << QString("mmesh::checkDegenerateFace true : [have degenerate face]");
			}

			input.mesh->clear_bbox();
			input.mesh->need_bbox();

			trimesh::vec3 offset;
			if(param.toCenter)
				offset = mmesh::moveTrimesh2Center(input.mesh.get(), false);

			ModelNDataPtr data(new ModelNData());
			data->mesh = input.mesh;
			data->input = input;
			data->offset = offset;

			trimesh::TriMesh* hull = qhullWrapper::convex_hull_3d(input.mesh.get());
			mmesh::dumplicateMesh(hull);

			data->hull.reset(hull);
			data->updateRenderData();

			return data;
		}

		return nullptr;
	}
}