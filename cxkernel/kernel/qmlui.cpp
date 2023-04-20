#include "qmlui.h"
#include <QtQml/QQmlComponent>
#include <QtCore/QDebug>
#include <QtQuick/QQuickImageProvider>

namespace cxkernel
{
	QmlUI::QmlUI(QObject* parent)
		: QObject(parent)
		, m_rootWindow(nullptr)
		, m_engine(nullptr)
		, m_context(nullptr)
	{

	}

	QmlUI::~QmlUI()
	{

	}

	QObject* QmlUI::createQmlObjectFromQrc(const QString& fileName)
	{
		QQmlComponent component(m_engine, QUrl::fromLocalFile(fileName));
		return component.create(m_context);
	}

	void QmlUI::registerContextObject(const QString& name, QObject* object)
	{
		if (!m_engine)
		{
			qWarning() << "QmlUI::registerContextObject: [Null Engine]";
			return;
		}

		if (!object)
			return;

		if (!object->parent())
		{
			qWarning() << "QmlUI::registerContextObject: [object without parent!!!]";
			m_engine->setObjectOwnership(object, QQmlEngine::ObjectOwnership::CppOwnership);
		}

		m_engine->rootContext()->setContextProperty(name, object);
	}

	void QmlUI::registerImageProvider(const QString& name, QQuickImageProvider* provider)
	{
		if (!m_engine)
		{
			qWarning() << "QmlUI::registerImageProvider: [Null Engine]";
			return;
		}

		m_engine->addImageProvider(name, provider);
	}

	void QmlUI::removeImageProvider(const QString& name)
	{
		if (!m_engine)
		{
			qWarning() << "QmlUI::removeImageProvider: [Null Engine]";
			return;
		}

		m_engine->removeImageProvider(name);
	}

	void QmlUI::setEngine(QQmlApplicationEngine* engine, QQmlContext* context)
	{
		m_engine = engine;
		m_context = context;
	}

	void QmlUI::registerRootWindow(QObject* object)
	{
		m_rootWindow = object;
	}

	QObject* QmlUI::itemByName(const QString& name)
	{
		if (!m_rootWindow)
			return nullptr;

		return m_rootWindow->findChild<QObject*>(name);
	}
}