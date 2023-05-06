#ifndef CXKERNEL_CAPTUREXENTITY_1681992284923_H
#define CXKERNEL_CAPTUREXENTITY_1681992284923_H
#include "cxkernel/cxkernelinterface.h"
#include "qtuser3d/refactor/xentity.h"

namespace cxkernel
{
	class CXKERNEL_API CaptureEntity : public qtuser_3d::XEntity
	{
	public:
		CaptureEntity(Qt3DCore::QNode* parent = nullptr);
		virtual ~CaptureEntity();

		void onCaptureComplete();

	protected:
	};
}

#endif // CXKERNEL_CAPTUREXENTITY_1681992284923_H