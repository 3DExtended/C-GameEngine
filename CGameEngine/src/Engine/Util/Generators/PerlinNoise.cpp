#include "PerlinNoise.h"
#include <SDL2/SDL.h>
using namespace ENGINE::UTIL;

PerlinNoise::PerlinNoise(long seed, int size)
	:size(size)
{
	std::srand(seed);
	InitPerlinNoise();
}

PerlinNoise::PerlinNoise(int size)
	:size(size)
{
	std::srand(SDL_GetTicks()*std::rand());

	InitPerlinNoise();
}

void PerlinNoise::InitPerlinNoise() {
	noise = std::vector<glm::vec2>(size*size);
	// Random Filling
	for (int i = 0; i < size*size; i++) {
		int a = std::rand();
		float af = (float)a / (float)RAND_MAX;
		int b = std::rand();
		float bf = (float)b / (float)RAND_MAX;
		noise[i] = glm::vec2(af, bf);
	}
}


PerlinNoise::~PerlinNoise()
{
}

float PerlinNoise::getRangeOne(float x, float y) {
	return (get(x, y) + 1.0f) / 2.0f;
}

float PerlinNoise::get(float x, float y)
{
	int minX = (int)x;
	int minY = (int)y;
	int maxX = minX + 1;
	int maxY = minY + 1;

	float g1 = glm::dot(noise[minX + size*minY], glm::vec2(x - (float)minX, y - (float)minY));
	float g2 = glm::dot(noise[maxX + size*minY], glm::vec2(x - (float)maxX, y - (float)minY));
	float g3 = glm::dot(noise[minX + size*maxY], glm::vec2(x - (float)minX, y - (float)maxY));
	float g4 = glm::dot(noise[maxX + size*maxY], glm::vec2(x - (float)maxX, y - (float)maxY));

	float u = fade(x - (float)minX);
	float v = fade(y - (float)minY);

	float x1 = lerp(g1, g2, u);
	float x2 = lerp(g3, g4, u);

	float out = lerp(x1, x2, v);

	return out;

}

float PerlinNoise::fade(float t) {
	// 6t^5 - 15t^4 + 10t^3
	return t * t * t * (t * (t * 6 - 15) + 10);
}

float PerlinNoise::lerp(float v0, float v1, float t) {
	return v0 + t*(v1 - v0);
}
