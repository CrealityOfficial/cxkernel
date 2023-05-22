#ifndef CXKERNEL_TOOLS_1684228095546_H
#define CXKERNEL_TOOLS_1684228095546_H
#include <QtCore/QObject>

namespace cxkernel
{
	class Tools : public QObject
	{
		Q_OBJECT
	public:
		Tools(QObject* parent = nullptr);
		virtual ~Tools();

		Q_INVOKABLE void shaderBinary();
		Q_INVOKABLE void autoGenerate(const QString& code);
	};
}

#endif // CXKERNEL_TOOLS_1684228095546_H