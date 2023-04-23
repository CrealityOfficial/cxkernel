#include "uiinterface.h"
#include "cxkernel/kernel/cxkernel.h"
#include "cxkernel/kernel/qmlui.h"

namespace cxkernel
{
	QObject* createQmlObjectFromQrc(const QString& fileName)
	{
		return cxKernel->qmlUI()->createQmlObjectFromQrc(fileName);
	}

	void registerContextObject(const QString& name, QObject* object)
	{
		cxKernel->qmlUI()->registerContextObject(name, object);
	}

	void registerImageProvider(const QString& name, QQuickImageProvider* provider)
	{
		cxKernel->qmlUI()->registerImageProvider(name, provider);
	}

	void removeImageProvider(const QString& name)
	{
		cxKernel->qmlUI()->removeImageProvider(name);
	}

	void setObjectOwnership(QObject* object)
	{
		cxKernel->qmlUI()->setObjectOwnership(object);
	}
}