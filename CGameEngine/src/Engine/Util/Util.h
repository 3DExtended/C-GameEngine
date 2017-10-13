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
		float colorpartToOneRange(uint8_t cPart);
		glm::vec3 colorToRGB(uint8_t r, uint8_t g, uint8_t b);

		std::vector<std::string> splitString(const std::string &s, char delim);
		void splitString(const std::string & s, char delim, std::vector<std::string>& elems);

	}
}