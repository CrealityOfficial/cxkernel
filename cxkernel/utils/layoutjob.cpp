#include "layoutjob.h"

namespace cxkernel
{
	LayoutItem::LayoutItem(cxkernel::CXModelPtr _model, QObject* parent)
		: QObject(parent)
		, model(_model)
	{

	}

	LayoutItem::~LayoutItem()
	{

	}

	trimesh::vec3 LayoutItem::position()
	{
		return model->position();
	}

	trimesh::box3 LayoutItem::globalBox()
	{
		return model->globalBox();
	}

	std::vector<trimesh::vec3> LayoutItem::outLine(bool global)
	{
		return model->outline_path(global);
	}

	std::vector<trimesh::vec3> LayoutItem::outLine_concave()
	{
		return model->concave_path();
	}

	LayoutJob::LayoutJob(QObject* parent)
		: Nest2DJob(parent)
		, m_lInsert(nullptr)
	{

	}

	LayoutJob::~LayoutJob()
	{

	}

	void LayoutJob::setModels(const QList<cxkernel::CXModelPtr>& models)
	{
		QList<qcxutil::PlaceItem*> items;
		for (cxkernel::CXModelPtr model : models)
		{
			LayoutItem* item = new LayoutItem(model, this);
			items.push_back(item);
			m_lItems.push_back(item);
		}
		setItems(items);
	}

	void LayoutJob::setInsert(cxkernel::CXModelPtr model)
	{
		m_lInsert = new LayoutItem(model, this);
		setInsertItem(m_lInsert);
	}

	void LayoutJob::successed(qtuser_core::Progressor* progressor)
	{
		auto f = [&](LayoutItem* item) {
			const qcxutil::NestResult& result = item->result;

			trimesh::vec3 pos = item->model->position();
			item->model->setPosition(trimesh::vec3(result.x, result.y, pos.z));

			trimesh::quaternion q = item->model->nestRotation();

			trimesh::quaternion dq = trimesh::quaternion::fromAxisAndAngle(trimesh::vec3(0.0f, 0.0f, 1.0f), -result.r);
			trimesh::quaternion rq = dq * q;

			item->model->setRotate(rq);
			item->model->dirtyNestData();
		};

		if (m_lInsert)
		{
			f(m_lInsert);
		}
		else {
			for (LayoutItem* item : m_lItems)
			{
				f(item);
			}
		}
	}
}