#include "TerrainGeneration.h"
#include "glm/gtc/constants.hpp"
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
TerrainGeneration::TerrainGeneration()
{

}

TerrainGeneration::TerrainGeneration(long seed1, long seed2, long seed3)
	:seed1(seed1), seed2(seed2), seed3(seed3)
{

}

Mesh * TerrainGeneration::createTerrainMesh(float sizeX, float sizeZ, float res)
{
	PerlinNoise* noiseHeightMap;
	PerlinNoise* noiseXOffset;
	PerlinNoise* noiseZOffset;


	if (seed1 == 0 && seed2 == 0 && seed3 == 0) {
		noiseHeightMap = new PerlinNoise(10 * (int)MAX(glm::ceil(sizeX + res), glm::ceil(sizeZ + res)));
		noiseXOffset = new PerlinNoise(10 * (int)MAX(glm::ceil(sizeX + res), glm::ceil(sizeZ + res)));
		noiseZOffset = new PerlinNoise(10 * (int)MAX(glm::ceil(sizeX + res), glm::ceil(sizeZ + res)));
	}
	else {
		noiseHeightMap = new PerlinNoise(seed1, 10 * (int)MAX(glm::ceil(sizeX + res), glm::ceil(sizeZ + res)));
		noiseXOffset = new PerlinNoise(seed2,	10 * (int)MAX(glm::ceil(sizeX + res), glm::ceil(sizeZ + res)));
		noiseZOffset = new PerlinNoise(seed3,	10 * (int)MAX(glm::ceil(sizeX + res), glm::ceil(sizeZ + res)));
	}

	
	
	

	Mesh *terrain = new Mesh();

	float startZ = -1.0f * sizeZ / 2.0f;
	float startX = -1.0f * sizeX / 2.0f;

	std::vector<glm::vec3> vertecies;

	int counterX = 0;
	int counterZ = 0;
	for (float z = startZ; z < sizeZ / 2.0f; z += res) {
		counterX = 0;
		for (float x = startX; x < sizeX / 2.0f; x += res) {
			counterX++;
			//position
			float height = noiseHeightMap->get((x + sizeX / 2.0f) / 2.0f, (z + sizeZ / 2.0f) / 2.0f)
				+ noiseHeightMap->get((x + sizeX / 2.0f)* 5.0f, (z + sizeZ / 2.0f)* 5.0f) / 2.0			//fine noise
				+ noiseHeightMap->get((x + sizeX / 2.0f) / 5.0f, (z + sizeZ / 2.0f) / 5.0f) * 3.0			//large noise
				+ 1.0f;

			const float dampenHill = 0.5f;
			//make hill from height
			float hillX = -glm::cos((x + sizeX / 2.0f) / sizeX * 2 * glm::pi<float>()) + 1;
			float hillZ = -glm::cos((z + sizeZ / 2.0f) / sizeZ * 2 * glm::pi<float>()) + 1;

			const float fineVSLarge = 0.2f;
			const float strength = 0.75f;

			glm::vec3 pos = glm::vec3(
				x + noiseXOffset->get((x + sizeX / 2.0f)*fineVSLarge, (z + sizeZ / 2.0f)*fineVSLarge) / strength * hillX * hillZ,
				height * hillX * hillZ * dampenHill,
				z + noiseZOffset->get((x + sizeX / 2.0f)*fineVSLarge, (z + sizeZ / 2.0f)*fineVSLarge) / strength * hillX * hillZ
			);

			vertecies.push_back(pos);

		}
		counterZ++;
	}


	//color
	glm::vec4 color(0.2, 0.9, 0.2, 1);

	for (int z = 0; z < counterZ - 1; z++) {
		for (int x = 0; x < counterX - 1; x++) {
			int a = terrain->addPoint(vertecies[(z + 1) * counterX + x], glm::vec3(0), glm::vec2(0), color, true);
			int b = terrain->addPoint(vertecies[z * counterX + (x + 1)], glm::vec3(0), glm::vec2(0), color, true);
			int c = terrain->addPoint(vertecies[z * counterX + x], glm::vec3(0), glm::vec2(0), color, true);

			terrain->addTriangleAndRecalcNormals(a, b, c);

			a = terrain->addPoint(vertecies[(z + 1) * counterX + x], glm::vec3(0), glm::vec2(0), color, true);
			b = terrain->addPoint(vertecies[z * counterX + (x + 1)], glm::vec3(0), glm::vec2(0), color, true);
			c = terrain->addPoint(vertecies[(z + 1) * counterX + (x + 1)], glm::vec3(0), glm::vec2(0), color, true);

			terrain->addTriangleAndRecalcNormals(c, b, a);

		}
	}

	return terrain;
}
