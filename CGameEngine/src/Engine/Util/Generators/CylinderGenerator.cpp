#include "CylinderGenerator.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
using namespace ENGINE;
using namespace ENGINE::UTIL;

Mesh * CylinderGenerator::createCylinder(float radius, unsigned int numberOfVerts, unsigned int numberOfHeightSections, float heightOfSection, glm::vec4 color)
{
	return createCylinder(radius, radius, numberOfVerts, numberOfHeightSections, heightOfSection, color);
}

Mesh * CylinderGenerator::createCylinder(float radiusBase, float radiusTop, unsigned int numberOfVerts,unsigned int numberOfHeightSections, float heightOfSection, glm::vec4 color)
{
	Mesh* cylinder = new Mesh();

	float angle = 360.0f / numberOfVerts;


	for(unsigned int y = 0 ; y <= numberOfHeightSections; y++){
		float radius = radiusBase + (radiusTop - radiusBase) / (float)numberOfHeightSections * (float) y;
		int id;
		for (unsigned int i = 0; i < numberOfVerts; i++) {
			
			glm::vec4 normal(radius, (float)y * heightOfSection, 0, 0);
			normal = glm::rotate(0.0174533f *angle * (float)i, glm::vec3(0, 1, 0)) * normal;

			id = cylinder->addPoint(glm::vec3(normal.x, normal.y, normal.z), glm::vec3(0), glm::vec2(0), color, true);

			if (y != 0 && i != 0) {
				int idprev = id - 1;
				int idDown = id - numberOfVerts;
				int idDownLeft = idDown - 1;


				cylinder->addTriangleAndRecalcNormalsFlatShader(idDownLeft, id, idprev);
				cylinder->addTriangleAndRecalcNormalsFlatShader(idDownLeft,idDown, id);

			}

		}

		if (y != 0) {
			//create last face by connecting last and first vertex in this row
			//id contains newest id
			int idprev = id - numberOfVerts + 1;
			int idDown = id - numberOfVerts;
			int idDownLeft = idprev - numberOfVerts;

			cylinder->addTriangleAndRecalcNormalsFlatShader(id, idDownLeft, idprev);
			cylinder->addTriangleAndRecalcNormalsFlatShader(id, idDown, idDownLeft);
		}
	}

	return cylinder;
}
