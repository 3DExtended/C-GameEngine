#pragma once
#include <string>
#include <fstream>
#include <streambuf>

namespace ENGINE {
	namespace UTIL {
		class FileSystem {
		public:
			static const std::string resFolderPrefix;
			static std::string LoadFile(const std::string fileName);

		};
	}
}