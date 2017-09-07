#include "Mesh.h"
using namespace ENGINE;
Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

int Mesh::addPoint(glm::vec3 vertexPos, glm::vec3 vertexNormal, glm::vec2 vertexTexture, glm::vec4 vertexColor)
{
	//first check if we already have this set of information
	uint32_t i = 0;
	while (i < (uint32_t)point.size()) {
		if (point[i] == vertexPos.x &&point[i + 1] == vertexPos.y && point[i + 2] == vertexPos.z)
			if (point[i + 3] == vertexNormal.x &&point[i + 4] == vertexNormal.y && point[i + 5] == vertexNormal.z)
				if (point[i + 6] == vertexTexture.x &&point[i + 7] == vertexTexture.y)
					if (point[i + 8] == vertexColor.x &&point[i + 9] == vertexColor.y && point[i + 10] == vertexColor.z&& point[i + 11] == vertexColor.w)
						return i / 12;
		i += 12;
	}

	//add a new set of floats to the points vector and return its index
	point.push_back(vertexPos.x);
	point.push_back(vertexPos.y);
	point.push_back(vertexPos.z);

	point.push_back(vertexNormal.x);
	point.push_back(vertexNormal.y);
	point.push_back(vertexNormal.z);

	point.push_back(vertexTexture.x);
	point.push_back(vertexTexture.y);

	point.push_back(vertexColor.x);
	point.push_back(vertexColor.y);
	point.push_back(vertexColor.z);
	point.push_back(vertexColor.w);

	return point.size() / 12 - 1;
}

void Mesh::addTriangle(uint32_t a, uint32_t b, uint32_t c)
{
	index.push_back(a);
	index.push_back(b);
	index.push_back(c);
}