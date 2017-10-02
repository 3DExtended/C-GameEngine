#include "Util.h"
void ENGINE::UTIL::splitString(const std::string &s, char delim, std::vector<std::string>& elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

void ENGINE::UTIL::printCurrentWorkingDirectory()
{
		char buffer[MAX_PATH];
		GetModuleFileNameA(NULL, buffer, MAX_PATH);
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		std::cout << std::string(buffer).substr(0, pos) << std::endl;
}

float ENGINE::UTIL::colorpartToOneRange(unsigned int cPart)
{
	return ((float)cPart)/255.0f;
}

glm::vec3 ENGINE::UTIL::colorToRGB(unsigned int r, unsigned int g, unsigned int b)
{
	return glm::vec3(colorpartToOneRange(r), colorpartToOneRange(g), colorpartToOneRange(b));
}

std::vector<std::string> ENGINE::UTIL::splitString(const std::string & s, char delim)
{
	std::vector<std::string> elems;
	splitString(s, delim, elems);
	return elems;
}