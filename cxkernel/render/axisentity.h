#ifndef CXKERNEL_AXISENTITY_1683287324896_H
#define CXKERNEL_AXISENTITY_1683287324896_H
#include "cxkernel/cxkernelinterface.h"
#include "qtuser3d/refactor/xentity.h"

namespace cxkernel
{
	enum class EAxis
	{
		ea_x,
		ea_y,
		ea_z
	};

	class CXKERNEL_API AxisEntity : public qtuser_3d::XEntity
	{
	public:
		AxisEntity(Qt3DCore::QNode* parent = nullptr);
		virtual ~AxisEntity();

		void setAxisEffect(qtuser_3d::XEffect* effect);
		void setAxisGeometry(Qt3DRender::QGeometry* geometry);
		void setAxisParameter(EAxis eaxis, const QString& name, const QVariant& value);
	protected:
		qtuser_3d::XEntity* m_entities[3];
	};
}

#endif // CXKERNEL_AXISENTITY_1683287324896_H