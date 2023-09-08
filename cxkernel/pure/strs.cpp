#include "strs.h"

#include <locale>
#include <codecvt>

namespace cxkernel
{
	std::string wstring2String(const std::wstring& wstr)
	{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;
		return converterX.to_bytes(wstr);
	}
}