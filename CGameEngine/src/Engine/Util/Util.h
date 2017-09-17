#pragma once
#include <glm/glm.hpp>
namespace ENGINE {
	namespace UTIL {
		float colorpartToOneRange(unsigned int cPart);
		glm::vec3 colorToRGB(unsigned int r, unsigned int g, unsigned int b);
	}
}