#include "const.h"
#include "buildinfo.h"

#include <fstream>

#include <QtCore/QCoreApplication>
#include <QtCore/QSettings>
#include <QtCore/QStandardPaths>
#include <QtCore/QDir>
#include <QtCore/QDebug>

#include "qtusercore/string/resourcesfinder.h"
#include "qtusercore/module/systemutil.h"

#pragma execution_character_set("utf-8")
namespace cxkernel
{
	CXKernelConst::CXKernelConst(QObject* parent)
		: QObject(parent)
	{
		m_version = QString("V%1.%2.%3.%4").arg(PROJECT_VERSION_MAJOR).arg(PROJECT_VERSION_MINOR).arg(PROJECT_VERSION_PATCH).arg(PROJECT_BUILD_ID);
		m_bundleName = QString("%1").arg(BUNDLE_NAME);
		m_os = QString("%1").arg(BUILD_OS);

		qApp->setOrganizationName(ORGANIZATION);
		qApp->setOrganizationDomain("CX");
		qApp->setApplicationName(PROJECT_NAME);
	}

	CXKernelConst::~CXKernelConst()
	{

	}

	const QString& CXKernelConst::version() const
	{
		return m_version;
	}

	const QString& CXKernelConst::os() const
	{
		return m_os;
	}

	const QString& CXKernelConst::bundleName() const
	{
		return m_bundleName;
	}

	QString CXKernelConst::writableLocation(const QString& subDir, const QString& subSubDir)
	{
		QString prefix = getCanWriteFolder();
		QString path = QString("%1/%2/").arg(prefix).arg(subDir);
		if (!subSubDir.isEmpty())
			path += subSubDir;

		QDir tempDir;
		if (!tempDir.exists(path))
		{
			tempDir.mkpath(path);
		}

		return path;
	}
}
