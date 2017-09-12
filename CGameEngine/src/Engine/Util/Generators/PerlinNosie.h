#pragma once
#include <glm/glm.hpp>
#include <vector>
namespace ENGINE {
	namespace UTIL {

		class PerlinNoise {
		public:
			PerlinNoise(long seed, int size);
			PerlinNoise(int size);
			~PerlinNoise();
			float get(float x, float y);
		private:
			std::vector<glm::vec2> noise;
			int size;
			float fade(float t);
			float lerp(float v0, float v1, float t);

			void InitPerlinNoise();
		};
	}
}