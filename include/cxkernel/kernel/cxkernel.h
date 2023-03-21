#ifndef CXKERNEL_CXKERNEL_1679400879176_H
#define CXKERNEL_CXKERNEL_1679400879176_H
#include "cxkernel/cxkernelinterface.h"
#include "qtuserquick/main/entry.h"

namespace cxkernel
{
	class CXKERNEL_API CXKernel : public QObject
								, public qtuser_quick::QmlAppModule
	{
	public:
		CXKernel(QObject* parent = nullptr);
		virtual ~CXKernel();

	protected:
		void beforeAppConstruct() override;
		void afterAppConstruct() override;

		void startLoadQmlEngine(QApplication& app, QQmlApplicationEngine& engine) override;
		void onAppEngineShutDown() override;
		void afterAppEngineShutDown() override;
	};

	extern CXKernel* cxKernel;
}

#endif // CXKERNEL_CXKERNEL_1679400879176_H