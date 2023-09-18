#include "entry.h"
#include <QtWidgets/QApplication>

#include <QtCore/QDebug>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QGuiApplication>
#include <QOpenGLContext>
#include <QtQuick/QQuickView>
#include <QFont>
#include "qtusercore/module/systemutil.h"
#include "cxkernel/utils/glcompatibility.h"
#include "frameless/FrameLessView.h"
#include <QIcon>

#include "ccglobal/log.h"

namespace cxkernel
{
	void outputMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg)
	{
#ifdef QT_NO_DEBUG
		QString text = QString("[%3]").arg(msg);
#else
#if DEBUG_FUNCTION
		QString text = QString("[FILE %1, FUNCTION %2][%3]").arg(context.file).arg(context.function).arg(msg);
#else
		QString text = QString("[%3]").arg(msg);
#endif
#endif
		switch (type)//log 信息类型
		{
		case QtDebugMsg:
			LOGD("%s", text.toLocal8Bit().constData());
			break;
		case QtInfoMsg:
			LOGI("%s", text.toLocal8Bit().constData());
			break;
		case QtWarningMsg:
			LOGW("%s", text.toLocal8Bit().constData());
			break;
		case QtCriticalMsg:
			LOGM("%s", text.toLocal8Bit().constData());
			break;
		case QtFatalMsg:
			LOGC("%s", text.toLocal8Bit().constData());
			break;
		default:
			LOGV("%s", text.toLocal8Bit().constData());
			break;
	}
}

	void initializeLog(int argc, char* argv[])
	{
#ifdef QT_NO_DEBUG

		qApp->setOrganizationName(ORGANIZATION);
		qApp->setOrganizationDomain("FDM");
		qApp->setApplicationName(PROJECT_NAME);//by TCJ "Creative3D"

		QString logDirectory = qtuser_core::getOrCreateAppDataLocation("Log");

		auto func = [](const char* name)->std::string {
			QString  dataTime = QDateTime::currentDateTime().toString("yyyy-MM-dd");
			dataTime += QString(".cxlog");
			return dataTime.toLocal8Bit().data();
		};

		LOGNAMEFUNC(func);
		LOGDIR(logDirectory.toLocal8Bit().data());
#else
		LOGCONSOLE();
#endif
		LOGLEVEL(1);

		qInstallMessageHandler(outputMessage);

		qDebug() << QString("----------> START LOG <-----------");
	}

	void uninitializeLog()
	{
		qDebug() << QString("----------> END LOG <-----------");
		LOGEND();
	}

	void setDefaultBeforApp()
	{
#ifdef Q_OS_OSX
		QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

		//dynamic plugin
		QStringList dynamicPathList = QCoreApplication::libraryPaths();

#ifdef Q_OS_OSX
		qDebug() << "OS OSX pre setDynamicLoadPath";
#elif defined Q_OS_WIN32
		qDebug() << "OS WIN32 pre setDynamicLoadPath";
#elif defined Q_OS_LINUX
		qDebug() << "OS LINUX pre setDynamicLoadPath";

		if (qEnvironmentVariableIsSet("APPDIR"))
		{
			QString appdir = qEnvironmentVariable("APPDIR");
			qDebug() << "Linux get the APPDIR : " << appdir;
			dynamicPathList << appdir + "/plugins";
		}
#endif

		qDebug() << "Pre Dynamic import paths:";
		qDebug() << dynamicPathList;
		QCoreApplication::setLibraryPaths(dynamicPathList);
	}

    void setDefaultQmlBeforeApp()
    {

    }

	void setDefaultQmlAfterApp(QQmlEngine& engine)
	{
		//qml plugin
		QStringList qmlPathList = engine.importPathList();

		QString applicationDir = QCoreApplication::applicationDirPath();
		qDebug() << "applicationDir " << applicationDir;

#ifdef Q_OS_OSX
		qDebug() << "OS OSX setQmlLoadPath";
		qmlPathList << applicationDir + "/../Resources/qml";
#elif defined Q_OS_WIN32
		qDebug() << "OS WIN32 setQmlLoadPath";
#elif defined Q_OS_LINUX
		qDebug() << "OS LINUX setQmlLoadPath";
		qmlPathList << applicationDir + "/lib/";
		qmlPathList << applicationDir + "/qml/";
#endif

		qDebug() << "Qml import paths:";
		qDebug() << qmlPathList;

		engine.setImportPathList(qmlPathList);
	}

	int appMain(int argc, char* argv[], AppModuleCreateFunc func)
	{
		initializeLog(argc, argv);

		setDefaultBeforApp();
		setBeforeApplication();
		setDefaultQmlBeforeApp();

		// Will make Qt3D and QOpenGLWidget share a common context
		QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

		QApplication app(argc, argv);
		app.setWindowIcon(QIcon(":/scence3d/res/logo.png"));


#ifdef Q_OS_OSX
		QQuickWindow::setTextRenderType(QQuickWindow::NativeTextRendering);
#endif

		AppModule* appModule = func ? func() : nullptr;
		int ret = 0;
		if (appModule)
		{
			{
				QFont default_font = QFont();
				default_font.setPointSize(9);
				app.setFont(default_font);

				FrameLessView view;
				view.setMinimumSize({ 1280, 720 });
				view.resize(1280, 720);
				view.moveToScreenCenter();

				QQmlEngine* engine = view.engine();

				setDefaultAfterApp();
				setDefaultQmlAfterApp(*engine);

				showDetailSystemInfo();

				if (appModule->loadQmlEngine(view, *engine))
				{
					view.show();
					ret = app.exec();
				}

				appModule->unloadQmlEngine();
			}
			appModule->shutDown();
			delete appModule;
		}

		uninitializeLog();
		return ret;
	}
}
