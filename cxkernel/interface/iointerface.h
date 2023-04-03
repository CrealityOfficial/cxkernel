#ifndef CREATIVE_KERNEL_IOINTERFACE_1673498671317_H
#define CREATIVE_KERNEL_IOINTERFACE_1673498671317_H
#include "cxkernel/cxkernelinterface.h"
#include "qtusercore/module/cxhandlerbase.h"
#include <QtCore/QString>

namespace cxkernel
{
	CXKERNEL_API void openLastSaveFolder();
	CXKERNEL_API void setIOFilterKey(const QString& filterKey);

	CXKERNEL_API void saveFile(qtuser_core::CXHandleBase* handler = nullptr, const QString& defaultName = QString());

	CXKERNEL_API void openFile(qtuser_core::CXHandleBase* handler = nullptr);
	CXKERNEL_API bool openFileWithName(const QString& fileName);
	CXKERNEL_API void openFileWithNames(const QStringList& fileNames);
	CXKERNEL_API bool openFileWithString(const QString& commonName);

	CXKERNEL_API void registerOpenHandler(qtuser_core::CXHandleBase* handler);
	CXKERNEL_API void registerSaveHandler(qtuser_core::CXHandleBase* handler);
	CXKERNEL_API void unRegisterOpenHandler(qtuser_core::CXHandleBase* handler);
	CXKERNEL_API void unRegisterSaveHandler(qtuser_core::CXHandleBase* handler);
}

#endif // CREATIVE_KERNEL_IOINTERFACE_1673498671317_H