#ifndef CXKERNEL_CXMODEL_1684898814122_H
#define CXKERNEL_CXMODEL_1684898814122_H
#include "cxkernel/render/modelentity.h"
#include "cxkernel/data/modelndata.h"

namespace cxkernel
{
	class CXKERNEL_API CXModel : public QObject
	{
	public:
		CXModel(ModelEntity* entity, QObject* parent = nullptr);
		virtual ~CXModel();

		void setData(ModelNDataPtr data);
		ModelNDataPtr data();
	protected:
		ModelEntity* m_entity;
		ModelNDataPtr m_data;
	};

	typedef QSharedPointer<CXModel> CXModelPtr;
}

#endif // CXKERNEL_CXMODEL_1684898814122_H