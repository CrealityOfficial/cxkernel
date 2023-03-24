#include "cxkernel/kernel/cxkernel.h"
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
#include <QtCore/QFile>

#include "qtuserqml/gl/rendermanager.h"

namespace cxkernel
{
	CXKernel* cxKernel = nullptr;
	CXKernel::CXKernel(QObject* parent)
		: QObject(parent)
		, m_engine(nullptr)
		, m_context(nullptr)
	{
		if (cxKernel)
			qDebug() << QString("CXKernel::CXKernel error. cxKernel intialized.");

		cxKernel = this;
		m_renderManager = new qtuser_qml::RenderManager(this);
	}

	CXKernel::~CXKernel()
	{

	}

	void CXKernel::initializeContext(QQmlApplicationEngine& engine)
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
		m_context->setContextProperty("kernel_kernel", this);

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
}