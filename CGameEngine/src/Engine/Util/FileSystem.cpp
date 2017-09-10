#include "FileSystem.h"

using namespace ENGINE::UTIL;
//TODO move this to a config file...
const std::string FileSystem::resFolderPrefix = "./";

std::string FileSystem::LoadFile(const std::string fileName)
{
	std::ifstream file(fileName.c_str(), std::ios::in);
	std::string res;
	std::getline(file, res,(char) file.eof());

	return res;
}

