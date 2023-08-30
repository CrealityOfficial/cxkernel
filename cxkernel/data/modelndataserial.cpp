#include "modelndataserial.h"

#include <QtCore/QDebug>
#include "cxnd/serial/trimeshserial.h"

namespace cxkernel
{
	ModelNDataSerial::ModelNDataSerial()
	{

	}

	ModelNDataSerial::~ModelNDataSerial()
	{

	}

	void ModelNDataSerial::setData(ModelNDataPtr data)
	{
		m_data = data;
	}

	ModelNDataPtr ModelNDataSerial::getData()
	{
		return m_data;
	}

	void ModelNDataSerial::load(const QString& fileName, ccglobal::Tracer* tracer)
	{
		if (m_data)
		{
			qDebug() << QString("ModelNDataSerial::load data must be null!");
			return;
		}

		m_data.reset(new ModelNData());

		QByteArray cdata = fileName.toLocal8Bit();
		bool result = cxnd::cxndLoad(*this, std::string(cdata), tracer);

		if (!result)
			m_data.reset();
	}

	void ModelNDataSerial::save(const QString& fileName, ccglobal::Tracer* tracer)
	{
		if (!m_data)
		{
			qDebug() << QString("ModelNDataSerial::save data must be valid!");
			return;
		}

		QByteArray cdata = fileName.toLocal8Bit();
		bool result = cxnd::cxndSave(*this, std::string(cdata), tracer);
		if(!result)
			qDebug() << QString("ModelNDataSerial::save error!");
	}

	int ModelNDataSerial::version()
	{
		return 0;
	}

	bool ModelNDataSerial::save(std::fstream& out, ccglobal::Tracer* tracer)
	{
		TriMeshPtr mesh = m_data->mesh;
		cxnd::saveTrimesh(out, mesh.get());

		cxnd::saveTrimesh(out, m_data->hull.get());
		cxnd::cxndSaveT<trimesh::vec3>(out, m_data->offset);
		return true;
	}

	bool ModelNDataSerial::load(std::fstream& in, int ver, ccglobal::Tracer* tracer)
	{
		if (ver == 0)
		{
			TriMeshPtr mesh(cxnd::loadTrimesh(in));
			if (!mesh)
				return false;

			m_data->mesh = mesh;
			m_data->input.description = QString("quick");
			m_data->input.mesh = mesh;

			TriMeshPtr hull(cxnd::loadTrimesh(in));
			m_data->hull = hull;
			cxnd::cxndLoadT<trimesh::vec3>(in, m_data->offset);
			return true;
		}

		return false;
	}
}