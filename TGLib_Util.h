#pragma once
#include "TGLib.h"
#include <vector>

namespace TGLib {

std::vector<std::string> TokenizeQuoted(const std::string& input);

std::wstring ToWide(const std::string& narrow);
std::string ToNarrow(const std::wstring& wide);

}