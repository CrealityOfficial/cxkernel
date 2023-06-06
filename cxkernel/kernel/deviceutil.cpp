#include "deviceutil.h"
#include "qtuser3d/module/glcompatibility.h"

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
		return qtuser_3d::isGles();
	}

	bool DeviceUtil::isSoftwareGL()
	{
		return qtuser_3d::isSoftwareGL();
	}
}