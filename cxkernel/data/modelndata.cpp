#include "modelndata.h"
#include "qcxutil/trimesh2/q3drender.h"
#include "qcxutil/trimesh2/trimesh2qgeometryrenderer.h"
#include "qtuser3d/geometry/geometrycreatehelper.h"
#include "qhullWrapper/hull/meshconvex.h"
#include "mmesh/trimesh/trimeshutil.h"
#include "polygonLib/polygonLib.h"

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

			trimesh::vec3 offset;
			if(param.toCenter)
				offset = mmesh::moveTrimesh2Center(input.mesh.get(), false);

			ModelNDataPtr data(new ModelNData());
			data->mesh = input.mesh;
			data->input = input;
			data->offset = offset;
			data->hull.reset(qhullWrapper::convex_hull_3d(input.mesh.get()));
			data->updateRenderData();

			return data;
		}

		return nullptr;
	}

	NestData::NestData()
		: nestRotation(0.0)
		, m_dirty(true)
	{
	}

	NestData::~NestData()
	{
	}

	void NestData::setDirty(bool dirty)
	{
		m_dirty = dirty;
	}

	bool NestData::dirty()
	{
		return m_dirty;
	}

	std::vector<trimesh::vec3> NestData::path(bool simple)
	{
		const std::vector<trimesh::vec3>& p = cPath(simple);

		std::vector<trimesh::vec3> result;
		double sinAng = std::sin(nestRotation * M_PIl / 180.0);
		double cosAng = std::cos(nestRotation * M_PIl / 180.0);

		for(const trimesh::vec3& v : p)
		{
			double x = v.x * cosAng - v.y * sinAng;
			double y = v.x * sinAng + v.y * cosAng;
			result.push_back(trimesh::vec3(x, y, 0.0f));
		};
		return result;
	}

	const std::vector<trimesh::vec3>& NestData::cPath(bool simple)
	{
		if (simple)
			return simples;
		return convex ? convex->vertices : simples;
	}

	std::vector<trimesh::vec3> NestData::concave_path(TriMeshPtr globalMesh)
	{
		std::vector<trimesh::vec3> lines;
		if (globalMesh)
		{
			globalMesh->need_bbox();
			trimesh::vec3 localPosition = globalMesh->bbox.center();

			double angle = nestRotation;
			double sinAng = std::sin(-angle * M_PIl / 180.0f);
			double cosAng = std::cos(-angle * M_PIl / 180.0f);
			auto moveAndRotPoint = [sinAng, cosAng](trimesh::vec3 pt, trimesh::vec3 axis)
			{
				pt = pt - axis;
				trimesh::vec3 result;
				result.x = pt.x * cosAng - pt.y * sinAng;
				result.y = pt.x * sinAng + pt.y * cosAng;
				return result;
			};

			std::vector<polygonLib::PointF> concaveHull;
			for (const trimesh::point& pt : globalMesh->vertices)
			{
				trimesh::vec3 pt_rot = moveAndRotPoint(pt, localPosition);
				concaveHull.push_back(polygonLib::PointF(pt_rot.x, pt_rot.y));
			}
			concaveHull = polygonLib::PolygonPro::polygonConcaveHull(concaveHull);

			for (const polygonLib::PointF& v : concaveHull)
			{
				lines.push_back(trimesh::vec3(v.x, v.y, 0.0f));
			}
		}

		return lines;
	}

	void NestData::copyData(const NestData* nd)
	{
		if (!nd)
			return;

		convex = nd->convex;
		simples = nd->simples;
		m_dirty = nd->m_dirty;
		nestRotation = nd->nestRotation;
	}

	void NestData::setNestRotation(double angle)
	{
		nestRotation = angle;
	}

	double NestData::getNestRotation()
	{
		return nestRotation;
	}

	void NestData::calculateXYConvex(TriMeshPtr hull, const trimesh::fxform& rxf, const trimesh::vec3& scale)
	{
		if (!dirty())
			return;

		if (hull)
		{
			convex.reset(qhullWrapper::convex2DPolygon(hull.get(), rxf, nullptr));

			for (trimesh::vec3& v : convex->vertices)
				v *= scale;

			trimesh::box3 box;
			for (const trimesh::vec3& v : convex->vertices)
				box += v;

			simples.clear();
			const trimesh::vec3& dmin = box.min;
			const trimesh::vec3& dmax = box.max;
			simples.push_back(trimesh::vec3(dmin.x, dmin.y, 0.0f));
			simples.push_back(trimesh::vec3(dmax.x, dmin.y, 0.0f));
			simples.push_back(trimesh::vec3(dmax.x, dmax.y, 0.0f));
			simples.push_back(trimesh::vec3(dmin.x, dmax.y, 0.0f));
			setDirty(false);
			setNestRotation(0.0);
		}
	}
}