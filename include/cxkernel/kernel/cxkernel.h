#ifndef CXKERNEL_CXKERNEL_1679400879176_H
#define CXKERNEL_CXKERNEL_1679400879176_H
#include "cxkernel/cxkernelinterface.h"
#include "qtuserquick/main/entry.h"

namespace qtuser_qml
{
	class RenderManager;
	class RenderItemWrapper;
}

class GLQuickItem;
namespace cxkernel
{
	class CXKERNEL_API CXKernel : public QObject
								, public qtuser_quick::AppModule
	{
		Q_OBJECT
	public:
		CXKernel(QObject* parent = nullptr);
		virtual ~CXKernel();

		Q_INVOKABLE void registerContextObject(const QString& name, QObject* object);
	protected:
		virtual void initializeContext();
		virtual void initialize();
		virtual void uninitialize();

		virtual QString entryQmlFile();
		bool loadQmlEngine(QApplication& app, QQmlApplicationEngine& engine) override;
		void unloadQmlEngine() override;
		void shutDown() override;

		Q_INVOKABLE void invokeFromQmlWindow();
		Q_INVOKABLE void exposureMainItem(GLQuickItem* item);
	protected:
		QQmlApplicationEngine* m_engine;
		QQmlContext* m_context;

		qtuser_qml::RenderManager* m_renderManager;
		qtuser_qml::RenderItemWrapper* m_renderWrapper;
	};

	extern CXKernel* cxKernel;
}

#endif // CXKERNEL_CXKERNEL_1679400879176_H