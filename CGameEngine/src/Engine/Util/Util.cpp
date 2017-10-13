#include "Util.h"
void ENGINE::UTIL::splitString(const std::string &s, char delim, std::vector<std::string>& elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

float ENGINE::UTIL::colorpartToOneRange(uint8_t cPart)
{
	return ((float)cPart)/255.0f;
}

glm::vec3 ENGINE::UTIL::colorToRGB(uint8_t r, uint8_t g, uint8_t b)
{
	return glm::vec3(colorpartToOneRange(r), colorpartToOneRange(g), colorpartToOneRange(b));
}

std::vector<std::string> ENGINE::UTIL::splitString(const std::string & s, char delim)
{
	std::vector<std::string> elems;
	splitString(s, delim, elems);
	return elems;
}