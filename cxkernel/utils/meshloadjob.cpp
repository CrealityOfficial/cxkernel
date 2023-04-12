#include "meshloadjob.h"

#include "qtusercore/module/progressortracer.h"
#include "qtusercore/string/resourcesfinder.h"

#include "stringutil/util.h"
#include "cxbin/load.h"

#include "cxkernel/interface/modelninterface.h"

namespace cxkernel
{
	MeshLoadJob::MeshLoadJob(QObject* parent)
		: Job(parent)
	{
	}

	MeshLoadJob::~MeshLoadJob()
	{
	}

	void MeshLoadJob::setFileName(const QString& fileName)
	{
		m_fileName = fileName;
	}

	QString MeshLoadJob::name()
	{
		return "Load Mesh";
	}

	QString MeshLoadJob::description()
	{
		return "Load Mesh.";
	}

	void MeshLoadJob::failed()
	{
		qDebug() << "MeshLoadJob::failed.";
	}

	void MeshLoadJob::successed(qtuser_core::Progressor* progressor)
	{
		QString shortName = m_fileName;
		QStringList stringList = shortName.split("/");
		if (stringList.size() > 0)
			shortName = stringList.back();

		ModelCreateInput input;
		input.mesh = m_mesh;
		input.fileName = m_fileName;
		input.name = shortName;
		input.type = ModelNDataType::mdt_file;
		addModelFromCreateInput(input);
	}

	void MeshLoadJob::work(qtuser_core::Progressor* progressor)
	{
		qtuser_core::ProgressorTracer tracer(progressor);

		std::wstring strWname = m_fileName.toStdWString();
		std::string strname = stringutil::wstring2string(strWname);
		m_mesh = TriMeshPtr(cxbin::loadAll(strname, &tracer));
	}
}
