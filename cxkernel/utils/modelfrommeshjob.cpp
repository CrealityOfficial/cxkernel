#include "modelfrommeshjob.h"

#include <QtCore/QDebug>

#include "data/modeln.h"
#include "mmesh/trimesh/trimeshutil.h"
#include "qhullWrapper/hull/meshconvex.h"
#include "qtusercore/module/progressortracer.h"

#include "interface/spaceinterface.h"
#include "interface/modelinterface.h"
#include "interface/uiinterface.h"

namespace creative_kernel
{
	ModelFromMeshJob::ModelFromMeshJob(QObject* parent)
		: Job(parent)
	{
	}

	ModelFromMeshJob::~ModelFromMeshJob()
	{
	}

	void ModelFromMeshJob::setInput(ModelCreateInput input)
	{
		m_input = input;
	}

	QString ModelFromMeshJob::name()
	{
		return "ModelFromMeshJob";
	}

	QString ModelFromMeshJob::description()
	{
		return "ModelFromMeshJob";
	}

	void ModelFromMeshJob::failed()
	{
		qDebug() << "fail";
	}

	void ModelFromMeshJob::successed(qtuser_core::Progressor* progressor)
	{
		qDebug() << "success";

		if (m_data)
		{
			creative_kernel::ModelN* model = new creative_kernel::ModelN();
			model->setData(m_data);

			qtuser_3d::Box3D baseBox = baseBoundingBox();
			qtuser_3d::Box3D modelBox = model->globalSpaceBox();

			if (modelBox.size().x() > baseBox.size().x() ||
				modelBox.size().y() > baseBox.size().y() ||
				modelBox.size().z() > baseBox.size().z())
			{
				appendResizeModel(model);
				requestQmlDialog("idModelUnfitMessageDlg");
			}
			else
			{ 
				addModelLayout(model);
			}
		}
	}

	void ModelFromMeshJob::work(qtuser_core::Progressor* progressor)
	{
		TriMeshPtr mesh = m_input.mesh;
		if (mesh)
		{
			qtuser_core::ProgressorTracer tracer(progressor);
			mesh->normals.clear();
			mmesh::dumplicateMesh(mesh.get(), &tracer);

			mesh->clear_bbox();
			mesh->need_bbox();
			mmesh::moveTrimesh2Center(mesh.get(), false);

			m_data.reset(new ModelNData());
			m_data->mesh = mesh;
			m_data->description = m_input.description;
			m_data->name = m_input.name;
			m_data->hull.reset(qhullWrapper::convex_hull_3d(mesh.get()));
			m_data->updateRenderData();
		}
	}
}
