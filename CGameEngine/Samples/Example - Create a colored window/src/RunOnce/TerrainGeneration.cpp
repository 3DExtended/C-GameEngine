#include "TerrainGeneration.h"
#include "glm/gtc/constants.hpp"
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MAXT(X, Y, Z) MAX( MAX((X),(Y)),(Z))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
TerrainGeneration::TerrainGeneration()
{

}

TerrainGeneration::TerrainGeneration(long seed)
	:seed(seed)
{

}

Mesh * TerrainGeneration::createTerrainMesh(float sizeX, float sizeZ, float res)
{
	this->sizeX = sizeX;
	this->sizeZ = sizeZ;
	

	if (seed == 0) {
		noiseHeightMap = new PerlinNoise(10 * (int)MAX(glm::ceil(sizeX + res), glm::ceil(sizeZ + res)));}
	else {
		noiseHeightMap = new PerlinNoise(seed, 10 * (int)MAX(glm::ceil(sizeX + res), glm::ceil(sizeZ + res)));
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

			//range -20 to 20
			float baseHeight = noiseHeightMap->get((x + sizeX / 2.0f) / 150.0f, (z + sizeZ / 2.0f) / 150.0f) ;
			baseHeight *= 20.0;

			float largeFreq = noiseHeightMap->get((x + sizeX / 2.0f) / 25.0f, (z + sizeZ / 2.0f) / 25.0f);
			largeFreq = noiseHeightMap->get((x + sizeX / 2.0f) / 25.0f, (z + sizeZ / 2.0f) / 25.0f) < 0.1 ? largeFreq : 0;

			float middleFreq = noiseHeightMap->get((x + sizeX / 2.0f) / 2.0f, (z + sizeZ / 2.0f) / 2.0f);
			middleFreq *= 0.5f;

			//baseHeight *= middleFreq + 1.0f;

			float lowFreq = noiseHeightMap->get((x + sizeX / 2.0f) / 0.1f, (z + sizeZ / 2.0f) / 0.1f);
			lowFreq *= 0.2f;

			float height = baseHeight + largeFreq + middleFreq + lowFreq;

			const float fineVSLarge = 0.2f;
			const float strength = 0.75f;

			glm::vec3 pos = glm::vec3(
				x,// + noiseXOffset->get((x + sizeX / 2.0f)*fineVSLarge, (z + sizeZ / 2.0f)*fineVSLarge) / strength * hillX * hillZ,
				height,
				z// + noiseZOffset->get((x + sizeX / 2.0f)*fineVSLarge, (z + sizeZ / 2.0f)*fineVSLarge) / strength * hillX * hillZ
			);

			vertecies.push_back(pos);

		}
		counterZ++;
	}
	

	for (int z = 0; z < counterZ - 1; z++) {
		for (int x = 0; x < counterX - 1; x++) {
			if (x % 2 == 0)
			{
				if (z % 2 == 0) {
					addTrianglesMode1(terrain, vertecies, counterX, counterZ, x, z);
				}
				else {
					addTrianglesMode2(terrain, vertecies, counterX, counterZ, x, z);
				}
			}
			else {
				if (z % 2 == 0) {
					addTrianglesMode2(terrain, vertecies, counterX, counterZ, x, z);
				}
				else {
					addTrianglesMode1(terrain, vertecies, counterX, counterZ, x, z);
				}
			}
		}
	}

	return terrain;
}

void TerrainGeneration::addTrianglesMode1(Mesh * terrain, std::vector<glm::vec3> vertecies, int counterX, int counterZ, int x, int z)
{
	glm::vec3 posA = vertecies[(z + 1) * counterX + x];
	glm::vec3 posB = vertecies[(z + 1) * counterX + (x + 1)];
	glm::vec3 posC = vertecies[z * counterX + x];

	glm::vec3 normal = CalculateNormal(posA, posB, posC);
	glm::vec4 color = CalculateColor((posA+posB+posC)/3.0f,normal);

	int a = terrain->addPoint(posA, normal, glm::vec2(0), color, true);
	int b = terrain->addPoint(posB, normal, glm::vec2(0), color, true);
	int c = terrain->addPoint(posC, normal, glm::vec2(0), color, true);

	terrain->addTriangle(a, b, c);


	posA = vertecies[(z + 1) * counterX + (x + 1)];
	posB = vertecies[z * counterX + (x + 1)];
	posC = vertecies[z * counterX + x];

	normal = CalculateNormal(posA, posB, posC);
	color = CalculateColor((posA + posB + posC) / 3.0f, normal);

	a = terrain->addPoint(posA, normal, glm::vec2(0), color, true);
	b = terrain->addPoint(posB, normal, glm::vec2(0), color, true);
	c = terrain->addPoint(posC, normal, glm::vec2(0), color, true);

	terrain->addTriangle(a, b, c);
}

void TerrainGeneration::addTrianglesMode2(Mesh * terrain, std::vector<glm::vec3> vertecies, int counterX, int counterZ, int x, int z)
{

	glm::vec3 posA = vertecies[(z + 1) * counterX + x];
	glm::vec3 posB = vertecies[z * counterX + (x + 1)];
	glm::vec3 posC = vertecies[z * counterX + x];

	glm::vec3 normal = CalculateNormal(posA, posB, posC);
	glm::vec4 color = CalculateColor((posA + posB + posC) / 3.0f, normal);

	int a = terrain->addPoint(posA, normal, glm::vec2(0), color, true);
	int b = terrain->addPoint(posB, normal, glm::vec2(0), color, true);
	int c = terrain->addPoint(posC, normal, glm::vec2(0), color, true);

	terrain->addTriangle(a, b, c);

	posA = vertecies[(z + 1) * counterX + x];
	posB = vertecies[z * counterX + (x + 1)];
	posC = vertecies[(z + 1) * counterX + (x + 1)];

	normal = CalculateNormal(posA, posC, posB);
	color = CalculateColor((posA + posB + posC) / 3.0f, normal);


	a = terrain->addPoint(posA, normal, glm::vec2(0), color, true);
	b = terrain->addPoint(posB, normal, glm::vec2(0), color, true);
	c = terrain->addPoint(posC, normal, glm::vec2(0), color, true);

	terrain->addTriangle(a, c, b);
}

glm::vec4 TerrainGeneration::CalculateColor(glm::vec3 averagePos, glm::vec3 normal)
{
	static float maxHeight = 0;
	maxHeight = MAX(maxHeight, averagePos.y);

	static float minHeight = 0;
	minHeight = MIN(minHeight, averagePos.y);

	//std::cout << "Max: " << maxHeight << ", Min: " << minHeight << std::endl;


	const int numberOfColors = 3;
	float thresholds[numberOfColors]{	-4.5f,		//wet sand
										-3.0f,		//sand
										1.45f };	//grass

	int i = 0;
	while (i < numberOfColors && thresholds[i] < averagePos.y) {
		i++;
	}

	glm::vec3 tempColor;
	switch (i)
	{
	case 0:
		tempColor = glm::vec3((float)155 / 255.0f, (float)120 / 255.0f, (float)85 / 255.0f);	//wet sand
		break;
	case 1:
		tempColor = glm::vec3((float)211 / 255.0f, (float)181 / 255.0f, (float)153 / 255.0f);	//sand
		break;
	case 2:
	default:
		tempColor = glm::vec3((float)105 / 255.0f, (float)150 / 255.0f, (float)72 / 255.0f);	//Grass
		break; 
	/*
		tempColor = glm::vec3((float)224 / 255.0f, (float)238 / 255.0f, (float)251 / 255.0f);	//Snow
		break;*/
	}

	normal = glm::normalize(normal);

	if (normal.y < 0.5) {
		tempColor = glm::vec3((float)91 / 255.0f, (float)100 / 255.0f, (float)107 / 255.0f);//Rock
	}

	float dot = glm::dot(normal, glm::vec3(0, 1, 0)) + 1.0f;
	dot /= -2.0;


	float ranNum = noiseHeightMap->getRangeOne((averagePos.x + sizeX / 2.0f) / 150.0f, (averagePos.z + sizeZ / 2.0f) / 150.0f);
	ranNum = (ranNum) / 20.0f * dot;

	return glm::vec4(tempColor.x +ranNum, tempColor.y +ranNum , tempColor.z + ranNum,1.0);
}

glm::vec3 TerrainGeneration::CalculateNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	glm::vec3 u = b - a;
	glm::vec3 v = c - a;
	glm::vec3 normal(u.y * v.z - u.z * v.y, u.z*v.x - u.x*v.z, u.x*v.y - u.y*v.x);
	return normal;
}


//This code create one solid mesh with shared vertecies... Not sure how useful it really is yet
/*
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


for (float z = startZ; z < sizeZ / 2.0f; z += res) {
for (float x = startX; x < sizeX / 2.0f; x += res) {
//color
glm::vec4 color(0.2, 0.9, 0.2, 1);

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

int pointID = terrain->addPoint(pos, glm::vec3(0), glm::vec2(0), color);

if (z != startZ && x != startX) {

int pointLeft = pointID - 1;
int pointDown = pointID - glm::ceil(sizeX / res);
int pointDownLeft = pointDown - 1;

terrain->addTriangleAndRecalcNormals(pointID, pointDownLeft, pointLeft);
terrain->addTriangleAndRecalcNormals(pointID, pointDown, pointDownLeft);

}

}
}

return terrain;
}*/