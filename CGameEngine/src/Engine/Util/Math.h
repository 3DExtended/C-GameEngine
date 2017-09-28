#pragma once
#include <glm/glm.hpp>
#include "Constants.h"
#include <cstdlib>
namespace ENGINE {
	namespace UTIL {
		glm::mat4 shearMatrix(float a, float b, float c, float d, float e, float f);

		float rand();
	}
}