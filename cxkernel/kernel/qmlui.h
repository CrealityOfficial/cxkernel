#ifndef CXKERNEL_QMLUI_1681975873018_H
#define CXKERNEL_QMLUI_1681975873018_H
#include "cxkernel/cxkernelinterface.h"
#include <QtQml/QQmlContext>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QJSValue>
#include <QtQml/QQmlExpression>

namespace cxkernel
{
	class QmlUI : public QObject
	{
		Q_OBJECT
	public:
		QmlUI(QObject* parent = nullptr);
		virtual ~QmlUI();

		QObject* createQmlObjectFromQrc(const QString& fileName);
		void registerContextObject(const QString& name, QObject* object);
		void registerImageProvider(const QString& name, QQuickImageProvider* provider);
		void removeImageProvider(const QString& name);

		void setObjectOwnership(QObject* object);
		void setEngine(QQmlApplicationEngine* engine, QQmlContext* context);
		Q_INVOKABLE void registerRootWindow(QObject* object);
		
		Q_INVOKABLE QObject* itemByName(const QString& name);

		Q_INVOKABLE QVariant invokeQmlJs(const QString& script);
		Q_INVOKABLE QJSValue invokeJS(const QString& script, const QString& name, QObject* context);
	protected:
		QQmlApplicationEngine* m_engine;
		QJSEngine* m_jsEngine;
		QQmlExpression* m_expression;

		QQmlContext* m_context;
		QObject* m_rootWindow;
	};
}

#endif // CXKERNEL_QMLUI_1681975873018_H