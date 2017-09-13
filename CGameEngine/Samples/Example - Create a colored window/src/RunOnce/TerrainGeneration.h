#pragma once
#include "Engine/Util/Generators/PerlinNosie.h"

#include "Engine/Mesh.h"
#include <glm/glm.hpp>
#include <iostream>
#include "Engine\Util\Constants.h"

using namespace ENGINE;
using namespace ENGINE::UTIL;

class TerrainGeneration {
public:
	TerrainGeneration();
	TerrainGeneration(long seed);
	Mesh* createTerrainMesh(float sizeX, float sizeY, float res);

private:
	long seed = 0;
	float sizeX, sizeZ;

	PerlinNoise* noiseHeightMap;

	void addTrianglesMode1(Mesh *terrain, std::vector<glm::vec3> vertecies, int counterX, int counterZ, int x, int z);
	void addTrianglesMode2(Mesh *terrain, std::vector<glm::vec3> vertecies, int counterX, int counterZ, int x, int z);

	glm::vec4 CalculateColor(glm::vec3 averageHeight, glm::vec3 normal);
	glm::vec3 CalculateNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c);
};