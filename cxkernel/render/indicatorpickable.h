#ifndef QTUSER_3D_INDICATOR_PICKABLE_H
#define QTUSER_3D_INDICATOR_PICKABLE_H

#include "cxkernel/cxkernelinterface.h"
#include "qtuser3d/module/pickable.h"
#include "worldindicatorentity.h"

namespace cxkernel
{
	class CXKERNEL_API IndicatorPickable : public qtuser_3d::Pickable
	{
		Q_OBJECT
	public:
		IndicatorPickable(QObject* parent = nullptr);
		virtual ~IndicatorPickable();

		void setPickableEntity(WorldIndicatorEntity * entity);

		int primitiveNum() override;
		
		bool isGroup() override;

		bool hoverPrimitive(int primitiveID) override;
		void unHoverPrimitive() override;

		void pick(int primitiveID) override;

	protected:
		void onStateChanged(qtuser_3d::ControlState state) override;
		void faceBaseChanged(int faceBase) override;
		
	protected:
		WorldIndicatorEntity* m_pickableEntity;
	};
}
#endif // QTUSER_3D_INDICATOR_PICKABLE_H