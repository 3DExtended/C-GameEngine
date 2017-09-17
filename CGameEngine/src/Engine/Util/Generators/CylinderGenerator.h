#pragma once

#include "../../Mesh.h"
namespace ENGINE {
	namespace UTIL {
		class CylinderGenerator {

		public:
			static Mesh * createCylinder(float radius, unsigned int numberOfVerts, unsigned int numberOfHeightSections, float heightOfSection, glm::vec4 color);
		private:


		};
	}
}