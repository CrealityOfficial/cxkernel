#include "cxkernel/kernel/cxkernel.h"
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
#include <QtCore/QFile>
#include <QQuickView>

#include "qtusercore/module/cxopenandsavefilemanager.h"
#include "qtusercore/module/creativeplugincenter.h"
#include "qtusercore/module/jobexecutor.h"
#include "qtusercore/util/undoproxy.h"

#if USE_CXCLOUD
#include <cxcloud/service_center.h>
#endif

#include "cxkernel/utils/meshloader.h"
#include "cxkernel/utils/dumpproxy.h"
#include "cxkernel/kernel/deviceutil.h"
#include "cxkernel/kernel/qmlui.h"
#include "cxkernel/kernel/const.h"
#include "cxkernel/utils/tools.h"

#include "cxkernel/interface/uiinterface.h"

namespace cxkernel
{
	CXKernel* cxKernel = nullptr;

	CXKernel::CXKernel(QObject* parent)
			: CXKernel{
					[this]() { return new CXKernelConst{ this }; },
					parent,
				} {}

	CXKernel::CXKernel(CXKernelConstCreater const_creater, QObject* parent)
			: ContextBase(parent)
			, m_engine(nullptr)
			, m_context(nullptr) {
		if (cxKernel) {
			qDebug() << QString("CXKernel::CXKernel error. cxKernel intialized.");
		}

		cxKernel = this;

		assert(const_creater != nullptr && "const_creater is nullptr");
		m_const = const_creater();

		m_ioManager = new qtuser_core::CXFileOpenAndSaveManager(this);
		m_creativePluginCenter = new qtuser_core::CreativePluginCenter(this);
		m_jobExecutor = new qtuser_core::JobExecutor(this);
		m_meshLoader = new MeshLoader(this);
		m_dumpProxy = new DumpProxy(this);
		m_undoProxy = new qtuser_core::UndoProxy(this);
#if USE_CXCLOUD
		cxcloud_ = new cxcloud::ServiceCenter(m_const->version(), this);
#endif
		m_qmlUI = new QmlUI(this);
		m_tools = new Tools(this);
		m_deviceUtil = new DeviceUtil(this);
	}

	// CXKernel::CXKernel(QObject* parent)
	// 	: ContextBase(parent)
	// 	, m_engine(nullptr)
	// 	, m_context(nullptr)
	// {
	// 	if (cxKernel)
	// 		qDebug() << QString("CXKernel::CXKernel error. cxKernel intialized.");

	// 	cxKernel = this;
	// 	m_const = new CXKernelConst(this);
	// 	m_ioManager = new qtuser_core::CXFileOpenAndSaveManager(this);
	// 	m_creativePluginCenter = new qtuser_core::CreativePluginCenter(this);
	// 	m_jobExecutor = new qtuser_core::JobExecutor(this);
	// 	m_meshLoader = new MeshLoader(this);
	// 	m_dumpProxy = new DumpProxy(this);
	// 	m_undoProxy = new qtuser_core::UndoProxy(this);
	// 	cxcloud_ = new cxcloud::ServiceCenter(m_const->version(), this);
	// 	m_qmlUI = new QmlUI(this);
	// 	m_tools = new Tools(this);
	// 	m_deviceUtil = new DeviceUtil(this);
	// }

	CXKernel::~CXKernel()
	{
	}

	void CXKernel::registerContextObject(const QString& name, QObject* object)
	{
		if (!m_context || !object)
		{
			qDebug() << QString("CXKernel::registerContextObject null context, or null object.");
			return;
		}


		m_context->setContextProperty(name, object);
	}

	void CXKernel::openMeshFile()
	{
		m_ioManager->open(m_meshLoader);
	}

	QVariant CXKernel::invokeScript(const QString& script)
	{
		return cxkernel::invokeQmlJs(script);
	}

	bool CXKernel::invokeScriptRet(const QString& script)
	{
		return m_qmlUI->invokeQmlJsRt(script);
	}

	void CXKernel::createPPlugin(const QString& name)
	{
		QString tool = "pplugin;" + name;
		m_tools->autoGenerate(tool);
	}

	void CXKernel::createVPlugin(const QString& name)
	{
		QString tool = "vplugin;" + name;
		m_tools->autoGenerate(tool);
	}

	void CXKernel::initializeContext()
	{

	}

	void CXKernel::initialize()
	{

	}

	void CXKernel::uninitialize()
	{
	}

	QString CXKernel::entryQmlFile()
	{
		return QLatin1String("qrc:/cxkernel/main.qml");
	}

	bool CXKernel::loadQmlEngine(QQuickView& view, QQmlEngine& engine)
	{
		m_engine = &engine;
		m_context = m_engine->rootContext();

		QString qml = entryQmlFile();
		QString checkQml = qml;
		QFile qmlFile(checkQml.replace("qrc:/", ":/"));

		if (!m_context || !qmlFile.exists())
			return false;

		//register context
		m_engine->setObjectOwnership(this, QQmlEngine::CppOwnership);
		m_engine->setObjectOwnership(&view, QQmlEngine::CppOwnership);
		view.rootContext()->setContextProperty("view", &view);
		view.rootContext()->setContextProperty("cxkernel_kernel", this);
		view.rootContext()->setContextProperty("cxkernel_const", m_const);
		view.rootContext()->setContextProperty("cxkernel_io_manager", m_ioManager);
		view.rootContext()->setContextProperty("cxkernel_job_executor", m_jobExecutor);
		view.rootContext()->setContextProperty("cxkernel_undo", m_undoProxy);
		view.rootContext()->setContextProperty("screenScaleFactor", 1);
#if USE_CXCLOUD
		view.rootContext()->setContextProperty("cxkernel_cxcloud", cxcloud_);
#endif
		view.rootContext()->setContextProperty("cxkernel_ui", m_qmlUI);
		view.rootContext()->setContextProperty("cxkernel_tools", m_tools);
		view.rootContext()->setContextProperty("cxkernel_device_util", m_deviceUtil);

		m_qmlUI->setEngine(m_engine, m_context);

		initializeContext();
		m_creativePluginCenter->load();
		view.setSource(QUrl(qml));
		return true;
	}

	void CXKernel::unloadQmlEngine()
	{
		uninitialize();
		m_creativePluginCenter->uninitialize();
	}

	void CXKernel::shutDown()
	{
	}

	void CXKernel::invokeFromQmlWindow()
	{
		m_ioManager->registerOpenHandler(m_meshLoader);

		initialize();
		m_creativePluginCenter->initialize();
	}

	void CXKernel::initializeDump(const QString& version, const QString& cloudId, const QString& path)
	{
		m_dumpProxy->initialize(version, cloudId, path);
	}

	qtuser_core::CreativePluginCenter* CXKernel::cxPluginCenter()
	{
		return m_creativePluginCenter;
	}

	qtuser_core::CXFileOpenAndSaveManager* CXKernel::ioManager()
	{
		return m_ioManager;
	}

	qtuser_core::JobExecutor* CXKernel::jobExecutor()
	{
		return m_jobExecutor;
	}

	DumpProxy* CXKernel::dumpProxy()
	{
		return m_dumpProxy;
	}

	MeshLoader* CXKernel::meshLoader()
	{
		return m_meshLoader;
	}

	qtuser_core::UndoProxy* CXKernel::undoProxy()
	{
		return m_undoProxy;
	}

#if USE_CXCLOUD
	cxcloud::ServiceCenter* CXKernel::cxcloud() {
		return cxcloud_;
	}
#endif

	QmlUI* CXKernel::qmlUI()
	{
		return m_qmlUI;
	}

	CXKernelConst* CXKernel::cxConst()
	{
		return m_const;
	}
}
