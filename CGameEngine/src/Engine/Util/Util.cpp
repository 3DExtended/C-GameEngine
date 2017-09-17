#include "Util.h"

float ENGINE::UTIL::colorpartToOneRange(unsigned int cPart)
{
	return ((float)cPart)/255.0f;
}

glm::vec3 ENGINE::UTIL::colorToRGB(unsigned int r, unsigned int g, unsigned int b)
{
	return glm::vec3(colorpartToOneRange(r), colorpartToOneRange(g), colorpartToOneRange(b));
}
