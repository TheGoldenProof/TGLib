#include "Util.h"
#include <sstream>
#include <iomanip>

namespace TGLib {

std::vector<std::string> TokenizeQuoted(const std::string& input) {
	std::istringstream stream;
	stream.str(input);
	std::vector<std::string> tokens;
	std::string token;

	while (stream >> std::quoted(token))
		tokens.push_back(std::move(token));

	return tokens;
}

std::wstring ToWide(const std::string& narrow) {
	wchar* wide = new wchar[narrow.size()+1];
	mbstowcs_s(nullptr, wide, narrow.size()+1, narrow.c_str(), _TRUNCATE);
	std::wstring ret(wide);
	delete[] wide;
	return ret;
}

std::string ToNarrow(const std::wstring& wide) {
	char* narrow = new char[wide.size()+1];
	wcstombs_s(nullptr, narrow, wide.size()+1, wide.c_str(), _TRUNCATE);
	std::string ret(narrow);
	delete[] narrow;
	return ret;
}

}