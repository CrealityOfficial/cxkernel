#include "cxkernel/kernel/cxkernel.h"
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
#include <QtCore/QFile>

#include "qtusercore/module/cxopenandsavefilemanager.h"
#include "qtusercore/module/creativeplugincenter.h"
#include "qtuserqml/gl/rendermanager.h"
#include "qtuserqml/gl/renderitemwrapper.h"

namespace cxkernel
{
	CXKernel* cxKernel = nullptr;
	CXKernel::CXKernel(QObject* parent)
		: QObject(parent)
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

		initializeContext();
		engine.load(QUrl(qml));
		return true;
	}

	void CXKernel::unloadQmlEngine()
	{
		uninitialize();
	}

	void CXKernel::shutDown()
	{

	}

	void CXKernel::invokeFromQmlWindow()
	{

		initialize();
	}

	void CXKernel::exposureMainItem(GLQuickItem* item)
	{
		if (!m_renderWrapper && item)
		{
			m_renderWrapper = new qtuser_qml::RenderItemWrapper(item, this);
			registerContextObject("cxkernel_render_wrapper", m_renderWrapper);
		}
	}
}