#ifndef CXKERNEL_CXKERNEL_1679400879176_H
#define CXKERNEL_CXKERNEL_1679400879176_H
#include "cxkernel/cxkernelinterface.h"
#include "qtuserquick/main/entry.h"
#include "qtusercore/module/contextbase.h"

namespace qtuser_qml
{
	class RenderManager;
	class RenderItemWrapper;
}

namespace qtuser_core
{
	class JobExecutor;
	class CreativePluginCenter;
	class ApplicationConfiguration;
	class CXFileOpenAndSaveManager;
}

class GLQuickItem;
namespace cxkernel
{
	class VisualScene;
	class MeshLoader;
	class DumpProxy;
	class CXKERNEL_API CXKernel : public qtuser_core::ContextBase
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

		void initializeDump(const QString& version, const QString& cloudId, const QString& path);
	public:
		qtuser_qml::RenderManager* renderManager();
		qtuser_qml::RenderItemWrapper* renderWrapper();
		qtuser_core::CreativePluginCenter* cxPluginCenter();
		qtuser_core::CXFileOpenAndSaveManager* ioManager();
		qtuser_core::JobExecutor* jobExecutor();
		DumpProxy* dumpProxy();
	protected:
		QQmlApplicationEngine* m_engine;
		QQmlContext* m_context;

		qtuser_qml::RenderManager* m_renderManager;
		qtuser_qml::RenderItemWrapper* m_renderWrapper;
		qtuser_core::CreativePluginCenter* m_creativePluginCenter;
		qtuser_core::CXFileOpenAndSaveManager* m_ioManager;
		qtuser_core::JobExecutor* m_jobExecutor;
		DumpProxy* m_dumpProxy;

		MeshLoader* m_meshLoader;
	};

	extern CXKernel* cxKernel;
}

#endif // CXKERNEL_CXKERNEL_1679400879176_H