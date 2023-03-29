#include "iointerface.h"
#include "cxkernel/kernel/cxkernel.h"
#include "qtusercore/module/cxopenandsavefilemanager.h"

namespace cxkernel
{
    void openLastSaveFolder()
    {
        cxKernel->ioManager()->openLastSaveFolder();
    }

    void setIOFilterKey(const QString& filterKey)
    {
        cxKernel->ioManager()->setFilterKey(filterKey);
    }

    void saveFile(qtuser_core::CXHandleBase* handler, const QString& defaultName)
    {
        cxKernel->ioManager()->save(handler, defaultName);
    }

    void openFile(qtuser_core::CXHandleBase* handler)
    {
        cxKernel->ioManager()->open(handler);
    }

    bool openFileWithName(const QString& fileName)
    {
        return cxKernel->ioManager()->openWithName(fileName);
    }

    void openFileWithNames(const QStringList& fileNames)
    {
        cxKernel->ioManager()->openWithNames(fileNames);
    }

    bool openFileWithString(const QString& commonName)
    {
        return cxKernel->ioManager()->openWithString(commonName);
    }

    void registerOpenHandler(qtuser_core::CXHandleBase* handler)
    {
        cxKernel->ioManager()->registerOpenHandler(handler);
    }

    void registerSaveHandler(qtuser_core::CXHandleBase* handler)
    {
        cxKernel->ioManager()->registerSaveHandler(handler);
    }

    void unRegisterOpenHandler(qtuser_core::CXHandleBase* handler)
    {
        cxKernel->ioManager()->unRegisterOpenHandler(handler);
    }

    void unRegisterSaveHandler(qtuser_core::CXHandleBase* handler)
    {
        cxKernel->ioManager()->unRegisterSaveHandler(handler);
    }
}