#pragma once

#include "../../Mesh.h"
namespace ENGINE {
	namespace UTIL {
		class IcosphereGenerator {

		public:
			static Mesh* createIcosphere(glm::vec3 size, unsigned int tesselationNumber, glm::vec4 color);
		private:
			static const std::vector<glm::vec3> vertices;

			static const std::vector<glm::i16vec3> triangles;

			static glm::vec3 GetMidpoint(glm::vec3 a, glm::vec3 b);
			static int GetIDOrCreate(std::vector<glm::vec3>& resVertices, glm::vec3 newVertex);

		};
	}
}