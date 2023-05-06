#include "capturexentity.h"
#include "cxkernel/render/modelsimpleeffect.h"

namespace cxkernel
{
	CaptureEntity::CaptureEntity(Qt3DCore::QNode* parent)
		:XEntity(parent)
	{
		setEffect(new ModelSimpleEffect());
	}

	CaptureEntity::~CaptureEntity()
	{

	}

	void CaptureEntity::onCaptureComplete()
	{
		setGeometry(nullptr);
	}

}