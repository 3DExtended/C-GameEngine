#pragma once
#include "Engine/Util/Generators/PerlinNosie.h"
#include "Engine/Mesh.h"
#include <glm/glm.hpp>

using namespace ENGINE;
using namespace ENGINE::UTIL;

class TerrainGeneration {
public:
	TerrainGeneration();
	TerrainGeneration(long seed1, long seed2, long seed3);
	Mesh* createTerrainMesh(float sizeX, float sizeY, float res);

private:
	long seed1 = 0, seed2 = 0, seed3 = 0;
};