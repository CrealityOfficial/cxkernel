#ifndef CXKERNEL_CXKERNEL_1679400879176_H
#define CXKERNEL_CXKERNEL_1679400879176_H

#include <functional>

#include "cxkernel/cxkernelinterface.h"
#include "qtuserquick/main/entry.h"
#include "qtusercore/module/contextbase.h"

namespace qtuser_core
{
	class JobExecutor;
	class CreativePluginCenter;
	class ApplicationConfiguration;
	class CXFileOpenAndSaveManager;
	class UndoProxy;
}

namespace cxcloud {

class ServiceCenter;

}  // namespace cxcloud

namespace cxkernel
{
	class MeshLoader;
	class DumpProxy;
	class QmlUI;

	class CXKernelConst;
	using CXKernelConstCreater = std::function<CXKernelConst*(void)>;

	class Tools;
	class DeviceUtil;
	class CXKERNEL_API CXKernel : public qtuser_core::ContextBase
								, public qtuser_quick::AppModule
	{
		Q_OBJECT
	public:
		CXKernel(QObject* parent = nullptr);
		CXKernel(CXKernelConstCreater const_creater, QObject* parent = nullptr);
		virtual ~CXKernel();

		Q_INVOKABLE void registerContextObject(const QString& name, QObject* object);
		Q_INVOKABLE void openMeshFile();
		Q_INVOKABLE QVariant invokeScript(const QString& script);
		Q_INVOKABLE bool invokeScriptRet(const QString& script);

		Q_INVOKABLE void createPPlugin(const QString& name);
		Q_INVOKABLE void createVPlugin(const QString& name);
	protected:
		virtual void initializeContext();
		virtual void initialize();
		virtual void uninitialize();

		virtual QString entryQmlFile();
		bool loadQmlEngine(QApplication& app, QQmlApplicationEngine& engine) override;
		void unloadQmlEngine() override;
		void shutDown() override;

		Q_INVOKABLE void invokeFromQmlWindow();

		void initializeDump(const QString& version, const QString& cloudId, const QString& path);
	public:
		qtuser_core::CreativePluginCenter* cxPluginCenter();
		qtuser_core::CXFileOpenAndSaveManager* ioManager();
		qtuser_core::JobExecutor* jobExecutor();
		DumpProxy* dumpProxy();
		MeshLoader* meshLoader();
		qtuser_core::UndoProxy* undoProxy();
		cxcloud::ServiceCenter* cxcloud();
		QmlUI* qmlUI();
		CXKernelConst* cxConst();
	protected:
		QQmlApplicationEngine* m_engine;
		QQmlContext* m_context;

		qtuser_core::CreativePluginCenter* m_creativePluginCenter;
		qtuser_core::CXFileOpenAndSaveManager* m_ioManager;
		qtuser_core::JobExecutor* m_jobExecutor;
		DumpProxy* m_dumpProxy;
		qtuser_core::UndoProxy* m_undoProxy;
		cxcloud::ServiceCenter* cxcloud_;
		QmlUI* m_qmlUI;
		CXKernelConst* m_const;
		DeviceUtil* m_deviceUtil;
		Tools* m_tools;

		MeshLoader* m_meshLoader;
	};

	extern CXKernel* cxKernel;
}

#endif // CXKERNEL_CXKERNEL_1679400879176_H
