#include "cxmodel.h"

namespace cxkernel
{
	CXModel::CXModel(ModelEntity* entity, QObject* parent)
		: QObject(parent)
		, m_entity(entity)
	{

	}

	CXModel::~CXModel()
	{

	}

	void CXModel::setData(ModelNDataPtr data)
	{
		m_data = data;
		
		m_entity->setGeometry(m_data ? m_data->createGeometry() : nullptr);
	}

	ModelNDataPtr CXModel::data()
	{
		return m_data;
	}
}