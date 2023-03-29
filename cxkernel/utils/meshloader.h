#ifndef _NULLSPACE_MESHLOADERWRAPPER_1590982007351_H
#define _NULLSPACE_MESHLOADERWRAPPER_1590982007351_H
#include "cxkernel/utils/meshloader.h"
#include "qtusercore/module/cxhandlerbase.h"

namespace cxkernel
{
	class MeshLoader : public QObject, public qtuser_core::CXHandleBase
	{
		Q_OBJECT
	public:
		MeshLoader(QObject* parent = nullptr);
		virtual ~MeshLoader();

		void load(const QStringList& fileNames);
	public:
		QString filter() override;
		void handle(const QString& fileName) override;
		void handle(const QStringList& fileNames) override;
	};
}
#endif // _NULLSPACE_MESHLOADERWRAPPER_1590982007351_H
