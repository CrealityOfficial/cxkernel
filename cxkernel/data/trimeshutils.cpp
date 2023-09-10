#include "trimeshutils.h"

#include "cxnd/utils/str.h"
#include "cxbin/load.h"
#include "cxbin/save.h"

namespace cxkernel
{
	void generateGeometryDataFromMesh(trimesh::TriMesh* mesh, cxkernel::GeometryData& data)
	{
		if (!mesh || (mesh->faces.size() == 0) || (mesh->vertices.size() == 0))
			return;

		int fcount = (int)mesh->faces.size();
		int count = fcount * 3;

		data.fcount = fcount;
		data.vcount = count;

		QByteArray& positionByteArray = data.position;
		QByteArray& normalByteArray = data.normal;
		QByteArray& texcoordArray = data.texcoord;
		QByteArray& colorArray = data.color;

		positionByteArray.resize(count * 3 * sizeof(float));
		normalByteArray.resize(count * 3 * sizeof(float));

		bool hasTex = true;
		if(hasTex)
			texcoordArray.resize(count * 2 * sizeof(float));

		bool hasColor = mesh->colors.size() > 0;
		if (hasColor)
			colorArray.resize(count * 3 * sizeof(float));

		if (count == (int)mesh->vertices.size())
		{
			memcpy(positionByteArray.data(), &mesh->vertices[0], positionByteArray.size());
			if (mesh->normals.size() != count)
			{
				mesh->need_normals();
				memcpy(normalByteArray.data(), &mesh->normals[0], normalByteArray.size());
			}
		}
		else
		{
			trimesh::vec3* vertexData = (trimesh::vec3*)positionByteArray.data();
			trimesh::vec3* normalData = (trimesh::vec3*)normalByteArray.data();
			trimesh::vec2* texcoordData = (trimesh::vec2*)texcoordArray.data();
			trimesh::vec3* colorData = (trimesh::vec3*)colorArray.data();

			for (int i = 0; i < fcount; ++i)
			{
				if (hasColor)
				{
					trimesh::Color c = mesh->colors.at(i);
					for (int j = 0; j < 3; ++j)
					{
						colorData[i * 3 + j] = c;
					}
				}

				trimesh::TriMesh::Face& f = mesh->faces.at(i);
				for (int j = 0; j < 3; ++j)
				{
					vertexData[i * 3 + j] = mesh->vertices.at(f[j]);
				}

				trimesh::vec3 v01 = mesh->vertices.at(f[1]) - mesh->vertices.at(f[0]);
				trimesh::vec3 v02 = mesh->vertices.at(f[2]) - mesh->vertices.at(f[0]);
				trimesh::vec3 n = v01 TRICROSS v02;
				trimesh::normalize(n);;

				for (int j = 0; j < 3; ++j)
				{
					normalData[i * 3 + j] = n;
				}

				if (texcoordArray.size() && hasTex)
				{
					if (i >= mesh->faceUVs.size()
						|| i >= mesh->textureIDs.size())
					{
						//ȷ������shader�е���������
						texcoordData[3 * i] = trimesh::vec2(-1.0, -1.0);
						texcoordData[3 * i + 1] = trimesh::vec2(-1.0, -1.0);
						texcoordData[3 * i + 2] = trimesh::vec2(-1.0, -1.0);
					}
					else
					{
						trimesh::TriMesh::Face& faceUV = mesh->faceUVs.at(i);

						trimesh::vec2 uv0(-1.0, -1.0);
						trimesh::vec2 uv1(-1.0, -1.0);
						trimesh::vec2 uv2(-1.0, -1.0);

						int textureID = mesh->textureIDs[i];
						if (textureID > -1 && !mesh->materials.empty())
						{
							const trimesh::Material& material = mesh->materials[textureID];
							const trimesh::vec2& map_startUV = material.map_startUVs[trimesh::Material::MapType::DIFFUSE];
							const trimesh::vec2& map_endUV = material.map_endUVs[trimesh::Material::MapType::DIFFUSE];
							int UVsizeMax = mesh->UVs.size();
							if (faceUV.x > -1.0 && (faceUV.x < UVsizeMax))
							{
								uv0 = mesh->UVs.at(faceUV.x);
								uv0 = map_startUV + uv0 * (map_endUV - map_startUV);
							}
							if (faceUV.y > -1.0 && (faceUV.y < UVsizeMax))
							{
								uv1 = mesh->UVs.at(faceUV.y);
								uv1 = map_startUV + uv1 * (map_endUV - map_startUV);
							}
							if (faceUV.z > -1.0 && (faceUV.z < UVsizeMax))
							{
								uv2 = mesh->UVs.at(faceUV.z);
								uv2 = map_startUV + uv2 * (map_endUV - map_startUV);
							}
						}

						texcoordData[3 * i] = trimesh::vec2(uv0.x, uv0.y);
						texcoordData[3 * i + 1] = trimesh::vec2(uv1.x, uv1.y);
						texcoordData[3 * i + 2] = trimesh::vec2(uv2.x, uv2.y);

#if 1
						texcoordData[3 * i] = trimesh::vec2(-1.0, -1.0);
						texcoordData[3 * i + 1] = trimesh::vec2(-1.0, -1.0);
						texcoordData[3 * i + 2] = trimesh::vec2(-1.0, -1.0);
#endif
					}
				}
			}
		}
	}

	void generateIndexGeometryDataFromMesh(trimesh::TriMesh* mesh, cxkernel::GeometryData& data)
	{
		if (!mesh || (mesh->faces.size() == 0) || (mesh->vertices.size() == 0))
			return;

		int fcount = (int)mesh->faces.size();
		int vcount = mesh->vertices.size();

		data.fcount = fcount;
		data.vcount = vcount;
		data.indiceCount = fcount * 3;

		QByteArray& positionByteArray = data.position;
		QByteArray& indiceArray = data.indices;

		positionByteArray.resize(data.vcount * 3 * sizeof(float));

		indiceArray.resize(fcount * 3 * sizeof(uint));

		uint* indiceData = (uint*)indiceArray.data();
		for (int i = 0; i < fcount; ++i)
		{
			trimesh::TriMesh::Face& f = mesh->faces.at(i);
			for (int j = 0; j < 3; ++j)
			{
				indiceData[i * 3 + j] = f[j];
			}

		}

		float* vertexData = (float*)positionByteArray.data();
		for (int i = 0; i < mesh->vertices.size(); i++)
		{
			for (int j = 0; j < 3; j++)
			{
				vertexData[i * 3 + j] = mesh->vertices.at(i).at(j);
			}

		}
	}

	TriMeshPtr loadMeshFromName(const QString& fileName, ccglobal::Tracer* tracer)
	{
		std::wstring strWname = fileName.toStdWString();
		std::string strname = cxnd::wstring2String(strWname);
		TriMeshPtr mesh(cxbin::loadAll(strname, tracer));
		return mesh;
	}

	void saveMesh(trimesh::TriMesh* mesh, const QString& fileName)
	{
		std::wstring strWname = fileName.toStdWString();
		std::string strname = cxnd::wstring2String(strWname);
		cxbin::save(strname, mesh, nullptr);
	}
}



