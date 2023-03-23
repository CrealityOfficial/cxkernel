#include "cxkernel/kernel/cxkernel.h"
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
#include <QtCore/QFile>

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
	}

	CXKernel::~CXKernel()
	{

	}

	void CXKernel::initialize(QQmlApplicationEngine& engine)
	{

	}

	void CXKernel::uninitialize()
	{

	}

	QString CXKernel::entryQmlFile()
	{
		return QLatin1String("qrc:/scence3d/res/main.qml");
		//engine.load(QUrl());
	}

	bool CXKernel::loadQmlEngine(QApplication& app, QQmlApplicationEngine& engine)
	{
		m_engine = &engine;
		m_context = m_engine->rootContext();

		QString qml = entryQmlFile();
		QFile qmlFile(qml);

		if (!m_context || !qmlFile.exists())
			return false;

		initialize(engine);
		return true;
	}

	void CXKernel::unloadQmlEngine()
	{
		uninitialize();
	}

	void CXKernel::shutDown()
	{

	}
}