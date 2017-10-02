#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <sstream>
#include <string>
#include <iostream>
#include <string>
#include <iostream>
namespace ENGINE {
	namespace UTIL {
		float colorpartToOneRange(unsigned int cPart);
		glm::vec3 colorToRGB(unsigned int r, unsigned int g, unsigned int b);

		std::vector<std::string> splitString(const std::string &s, char delim);
		void splitString(const std::string & s, char delim, std::vector<std::string>& elems);

	}
}