#ifndef CXKERNEL_GLOBALCONST_1672882923747_H
#define CXKERNEL_GLOBALCONST_1672882923747_H

#include <QtCore/QObject>
#include "cxkernel/cxkernelinterface.h"

namespace cxkernel
{
	class CXKERNEL_API CXKernelConst : public QObject
	{
		Q_OBJECT
	public:
		CXKernelConst(QObject* parent = nullptr);
		virtual ~CXKernelConst();

		Q_INVOKABLE const QString& version() const;
		Q_INVOKABLE const QString& os() const;
		Q_INVOKABLE const QString& bundleName() const;

		QString writableLocation(const QString& subDir, const QString& subSubDir = QString());
	protected:
		QString m_version;
		QString m_os;
		QString m_bundleName;
	};
}

#endif // CXKERNEL_GLOBALCONST_1672882923747_H
