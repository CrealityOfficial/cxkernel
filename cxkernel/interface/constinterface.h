#ifndef XCKERNEL_APP_SETTING_INTERFACE_1593676766939_H
#define XCKERNEL_APP_SETTING_INTERFACE_1593676766939_H
#include "cxkernel/cxkernelinterface.h"
#include <QColor>
#include <QString>

namespace cxkernel
{
	CXKERNEL_API QString version();

	CXKERNEL_API QString writableLocation(const QString& subDir, const QString& subSubDir = QString());
}

#endif // XCKERNEL_APP_SETTING_INTERFACE_1593676766939_H