#ifndef CXKERNEL_UIINTERFACE_1681977959351_H
#define CXKERNEL_UIINTERFACE_1681977959351_H
#include "cxkernel/cxkernelinterface.h"
#include <QtQuick/QQuickImageProvider>

namespace cxkernel
{
	CXKERNEL_API QObject* createQmlObjectFromQrc(const QString& fileName);

	CXKERNEL_API void registerContextObject(const QString& name, QObject* object);
	CXKERNEL_API void registerImageProvider(const QString& name, QQuickImageProvider* provider);
	CXKERNEL_API void removeImageProvider(const QString& name);

	CXKERNEL_API void setObjectOwnership(QObject* object);
}

#endif // CXKERNEL_UIINTERFACE_1681977959351_H