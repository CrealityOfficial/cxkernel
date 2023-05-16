#include "tools.h"

#define INVOKE_BINARY
#include "qtuser3d/../tools/ShaderBinarization.cpp"
#undef INVOKE_BINARY

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
}