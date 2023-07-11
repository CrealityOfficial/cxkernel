#ifndef _LAYOUTJOB_1685524374981_H
#define _LAYOUTJOB_1685524374981_H
#include "qcxutil/util/nest2djob.h"
#include "cxkernel/flow/cxmodel.h"

namespace cxkernel
{
	class CXKERNEL_API LayoutItem : public QObject,
		public qcxutil::PlaceItem
	{
	public:
		LayoutItem(cxkernel::CXModelPtr model, QObject* parent = nullptr);
		virtual ~LayoutItem();

	protected:
		trimesh::vec3 position() override;
		trimesh::box3 globalBox() override;
		std::vector<trimesh::vec3> outLine(bool global) override;
		std::vector<trimesh::vec3> outLine_concave() override;

	public:
		cxkernel::CXModelPtr model;
	};

	class CXKERNEL_API LayoutJob : public qcxutil::Nest2DJob
	{
	public:
		LayoutJob(QObject* parent = nullptr);
		~LayoutJob();

		void setModels(const QList<cxkernel::CXModelPtr>& models);
		void setInsert(cxkernel::CXModelPtr model);
	protected:
		void successed(qtuser_core::Progressor* progressor) override;
	protected:
		QList<LayoutItem*> m_lItems;
		LayoutItem* m_lInsert;
	};
}
#endif // _LAYOUTJOB_1685524374981_H