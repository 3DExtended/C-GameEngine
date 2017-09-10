#pragma once
#include <string>
namespace ENGINE {
	namespace UTIL {
		struct CmpStr {
			bool operator()(const std::string a, const std::string b) const {
				return strcmp(a.c_str(), b.c_str()) < 0;
			}
		};
	}
}