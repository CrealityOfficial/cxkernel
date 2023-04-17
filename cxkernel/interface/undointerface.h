#ifndef CREATIVE_KERNEL_UNDOINTERFACE_1592736512631_H
#define CREATIVE_KERNEL_UNDOINTERFACE_1592736512631_H
#include "cxkernel/cxkernelinterface.h"
#include "qtusercore/util/undoproxy.h"
#include <QtWidgets/QUndoStack>

namespace cxkernel
{
	CXKERNEL_API void setUndoStack(QUndoStack* undoStack);

	CXKERNEL_API void undo();
	CXKERNEL_API void redo();

	CXKERNEL_API void addUndoCallback(qtuser_core::UndoCallback* callback);
	CXKERNEL_API void removeUndoCallback(qtuser_core::UndoCallback* callback);
}

#endif // CREATIVE_KERNEL_UNDOINTERFACE_1592736512631_H