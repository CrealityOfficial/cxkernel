#ifndef _NULLSPACE_BASICKERNELEXPORT_1589691866012_H
#define _NULLSPACE_BASICKERNELEXPORT_1589691866012_H
#include <QtCore/QObject>

#if defined(CXKERNEL_DLL)
#  define CXKERNEL_API Q_DECL_EXPORT
#else
#  define CXKERNEL_API Q_DECL_IMPORT
#endif

#endif // _NULLSPACE_BASICKERNELEXPORT_1589691866012_H
