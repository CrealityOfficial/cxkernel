#include "tools.h"

#define INVOKE_BINARY
#include "qtuser3d/../tools/ShaderBinarization.cpp"
#undef INVOKE_BINARY

#include "qtusercore/auto/templatelibrary.h"
#include "qtusercore/auto/keywordlist.h"
#include <QtCore/QDebug>

namespace cxkernel
{
	Tools::Tools(QObject* parent)
		: QObject(parent)
	{

	}

	Tools::~Tools()
	{

	}

	void Tools::shaderBinary()
	{
		invoke_shader_binary(0, nullptr);
	}

	void Tools::autoGenerate(const QString& code)
	{
		QStringList codes = code.split(";");
		if (codes.size() <= 1 )
		{
			qDebug() << QString("Tools::autoGenerate error code [%1]").arg(code);
			return;
		}

		QString templateName = codes.at(0);

		qtuser_core::TemplateLibrary library;
		QString templatePath = SOURCE_ROOT + QString("/qtuser/core/qtusercore/auto/templates/");

		QStringList pathList;
		pathList << templatePath;
		library.addSearchPath(pathList);

		qtuser_core::Template* t = library.get(templateName);
		if (!t)
		{
			qDebug() << QString("Tools::autoGenerate error. no template [%1]").arg(templateName);
			return;
		}

		codes.pop_front();
		QStringList names = codes.at(0).split("-");
		codes.pop_front();

		QHash<QString, QString> values;
		for (const QString& subKeys : codes)
		{
			QStringList kv = subKeys.split("-");
			if (kv.size() == 2)
			{
				values.insert(kv.at(0), kv.at(1));
			}
		}
		
		QString directory = BINARY_ROOT + QString("../");

		qtuser_core::KeywordList keywordList;
		for (const QString name : names)
		{
			values["name"] = name;
			keywordList.updateList(values);
			keywordList.setDirectory(directory);
			t->write(&keywordList);
		}
	}
}