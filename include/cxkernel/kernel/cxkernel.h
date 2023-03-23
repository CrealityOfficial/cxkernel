#ifndef CXKERNEL_CXKERNEL_1679400879176_H
#define CXKERNEL_CXKERNEL_1679400879176_H
#include "cxkernel/cxkernelinterface.h"
#include "qtuserquick/main/entry.h"

namespace cxkernel
{
	class CXKERNEL_API CXKernel : public QObject
								, public qtuser_quick::AppModule
	{
		Q_OBJECT
	public:
		CXKernel(QObject* parent = nullptr);
		virtual ~CXKernel();

		virtual void initialize(QQmlApplicationEngine& engine);
		virtual void uninitialize();
	protected:
		virtual QString entryQmlFile();
		bool loadQmlEngine(QApplication& app, QQmlApplicationEngine& engine) override;
		void unloadQmlEngine() override;
		void shutDown() override;
	protected:
		QQmlApplicationEngine* m_engine;
		QQmlContext* m_context;
	};

	extern CXKernel* cxKernel;
}

#endif // CXKERNEL_CXKERNEL_1679400879176_H