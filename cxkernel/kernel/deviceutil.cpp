#include "deviceutil.h"
#include "qtusercore/module/glcompatibility.h"

namespace cxkernel
{
	DeviceUtil::DeviceUtil(QObject* parent)
		: QObject(parent)
	{

	}

	DeviceUtil::~DeviceUtil()
	{

	}

	bool DeviceUtil::isDesktopGL()
	{
		return !isGles() && !isSoftwareGL();
	}

	bool DeviceUtil::isGles()
	{
		return qtuser_core::isGles();
	}

	bool DeviceUtil::isSoftwareGL()
	{
		return qtuser_core::isSoftwareGL();
	}
}