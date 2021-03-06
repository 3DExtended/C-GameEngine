#pragma once

#include "../../Mesh.h"
namespace ENGINE {
	namespace UTIL {
		class CylinderGenerator {

		public:
			static Mesh * createCylinder(float radius, unsigned int numberOfVerts, unsigned int numberOfHeightSections, float heightOfSection, glm::vec4 color);
			static Mesh * createCylinder(float radiusBase, float radiusTop, unsigned int numberOfVerts, unsigned int numberOfHeightSections, float heightOfSection, glm::vec4 color, bool closeTop = true);
		private:


		};
	}
}