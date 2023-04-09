#include "cxkernel/kernel/cxkernel.h"
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
#include <QtCore/QFile>

#include "qtusercore/module/cxopenandsavefilemanager.h"
#include "qtusercore/module/creativeplugincenter.h"
#include "qtusercore/module/jobexecutor.h"
#include "qtuserqml/gl/rendermanager.h"
#include "qtuserqml/gl/renderitemwrapper.h"

#include "cxkernel/kernel/visualscene.h"
#include "cxkernel/utils/meshloader.h"
#include "cxkernel/utils/dumpproxy.h"

#include "cxkernel/interface/renderinterface.h"

namespace cxkernel
{
	CXKernel* cxKernel = nullptr;
	CXKernel::CXKernel(QObject* parent)
		: ContextBase(parent)
		, m_engine(nullptr)
		, m_context(nullptr)
		, m_renderWrapper(nullptr)
	{
		if (cxKernel)
			qDebug() << QString("CXKernel::CXKernel error. cxKernel intialized.");

		cxKernel = this;
		m_renderManager = new qtuser_qml::RenderManager(this);
		m_ioManager = new qtuser_core::CXFileOpenAndSaveManager(this);
		m_creativePluginCenter = new qtuser_core::CreativePluginCenter(this);
		m_jobExecutor = new qtuser_core::JobExecutor(this);
		m_meshLoader = new MeshLoader(this);
		m_dumpProxy = new DumpProxy(this);
	}

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

	bool CXKernel::loadQmlEngine(QApplication& app, QQmlApplicationEngine& engine)
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
		m_context->setContextProperty("cxkernel_kernel", this);
		m_context->setContextProperty("cxkernel_io_manager", m_ioManager);
		m_context->setContextProperty("cxkernel_job_executor", m_jobExecutor);

		initializeContext();
		m_creativePluginCenter->load();

		engine.load(QUrl(qml));
		return true;
	}

	void CXKernel::unloadQmlEngine()
	{
		uninitialize();

		if (m_renderWrapper)
		{
			m_renderWrapper->uninitialize();
		}

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

	void CXKernel::exposureMainItem(GLQuickItem* item)
	{
		if (!m_renderWrapper && item)
		{
			m_renderWrapper = new qtuser_qml::RenderItemWrapper(item, this);
			registerContextObject("cxkernel_render_wrapper", m_renderWrapper);
		}
	}

	void CXKernel::initializeDump(const QString& version, const QString& cloudId, const QString& path)
	{
		m_dumpProxy->initialize(version, cloudId, path);
	}

	qtuser_qml::RenderManager* CXKernel::renderManager()
	{
		return m_renderManager; 
	}

	qtuser_qml::RenderItemWrapper* CXKernel::renderWrapper()
	{
		return m_renderWrapper;
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
}