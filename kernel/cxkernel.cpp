#include "cxkernel/kernel/cxkernel.h"
#include <QtCore/QDebug>

namespace cxkernel
{
	CXKernel* cxKernel = nullptr;
	CXKernel::CXKernel(QObject* parent)
		:QObject(parent)
	{
		if (cxKernel)
			qDebug() << QString("CXKernel::CXKernel error. cxKernel intialized.");

		cxKernel = this;
	}

	CXKernel::~CXKernel()
	{

	}

	void CXKernel::beforeAppConstruct()
	{

	}

	void CXKernel::afterAppConstruct()
	{

	}

	void CXKernel::startLoadQmlEngine(QApplication& app, QQmlApplicationEngine& engine)
	{

	}

	void CXKernel::onAppEngineShutDown()
	{

	}

	void CXKernel::afterAppEngineShutDown()
	{

	}
}