#include "IcosphereGenerator.h"
#include <algorithm>
using namespace ENGINE;
using namespace ENGINE::UTIL;

const float t = 0.850650808352039932181540f;
const float one = 0.5257311121191336060256693f;

const std::vector<glm::vec3> IcosphereGenerator::vertices =
{
	{ -one,t,0 },{ one,t,0 },{ -one,-t,0 },{ one,-t,0 },
	{ 0,-one,t },{ 0,one,t },{ 0,-one,-t },{ 0,one,-t },
	{ t,0,-one },{ t,0,one },{ -t,0,-one },{ -t,0,one }
};

const std::vector<glm::i16vec3> IcosphereGenerator::triangles =
{
	{ 0,11,5 },{ 0,5,1 },{ 0,1,7 },{ 0,7,10 },{ 0,10,11 },
	{ 1,5,9 },{ 5,11,4 },{ 11,10,2 },{ 10,7,6 },{ 7,1,8 },
	{ 3,9,4 },{ 3,4,2 },{ 3,2,6 },{ 3,6,8 },{ 3,8,9 },
	{ 4,9,5 },{ 2,4,11 },{ 6,2,10 },{ 8,6,7 },{ 9,8,1 }
};

Mesh * IcosphereGenerator::createIcosphere(glm::vec3 size, unsigned int tesselationNumber, glm::vec4 color)
{
	//create perfect round sphere and then scale it.
	std::vector<glm::vec3> resVertices;
	for (int i = 0; i < vertices.size(); i++) {
		resVertices.push_back(vertices[i]);
	}

	std::vector<glm::i16vec3> faces;
	for (int i = 0; i < triangles.size(); i++) {
		faces.push_back(triangles[i]);
	}

	//subdivide faces
	for (int i = 0; i < tesselationNumber; i++) {
		std::vector<glm::i16vec3> newFaces;
		for (int j = 0; j < faces.size(); j++) {
			glm::i16vec3 face = faces[j];

			int IDA = face.x;
			int IDB = face.y;
			int IDC = face.z;

			glm::vec3 posA = resVertices[IDA];
			glm::vec3 posB = resVertices[IDB];
			glm::vec3 posC = resVertices[IDC];

			glm::vec3 midAB = GetMidpoint(posA, posB);
			glm::vec3 midAC = GetMidpoint(posA, posC);
			glm::vec3 midBC = GetMidpoint(posB, posC);


			//handle midAB
			int idOfMidAB = GetIDOrCreate(resVertices, midAB);
			int idOfMidAC = GetIDOrCreate(resVertices, midAC);
			int idOfMidBC = GetIDOrCreate(resVertices, midBC);

			//create four new faces
			newFaces.push_back(glm::i16vec3(IDA, idOfMidAB, idOfMidAC));
			newFaces.push_back(glm::i16vec3(idOfMidAB, IDB, idOfMidBC));
			newFaces.push_back(glm::i16vec3(idOfMidAB, idOfMidBC, idOfMidAC));
			newFaces.push_back(glm::i16vec3(idOfMidAC, idOfMidBC,IDC));
		}

		//transfer newfaces to faces
		faces.clear();
		for (int i = 0; i < newFaces.size(); i++) {
			faces.push_back(newFaces[i]);
		}
		newFaces.clear();

	}

	//create mesh
	Mesh * mesh = new Mesh();
	for (int i = 0; i < faces.size(); i++) {
		glm::vec3 posA = resVertices[faces[i].x];
		glm::vec3 posB = resVertices[faces[i].y];
		glm::vec3 posC = resVertices[faces[i].z];

		//midpoint of posA, posB and posC is normal direction since we work on the unit sphere
		glm::vec3 normal = glm::normalize(
			glm::vec3(
				(posA.x + posB.x + posC.x) / 3.0f, 
				(posA.y + posB.y + posC.y) / 3.0f, 
				(posA.z + posB.z + posC.z) / 3.0f
			)
		);

		int ida = mesh->addPoint(posA, normal, glm::vec2(0), color, true);
		int idb = mesh->addPoint(posB, normal, glm::vec2(0), color, true);
		int idc = mesh->addPoint(posC, normal, glm::vec2(0), color, true);

		mesh->addTriangle(ida, idb, idc);
	}
	return mesh;
}

int IcosphereGenerator::GetIDOrCreate(std::vector<glm::vec3>& resVertices, glm::vec3 newVertex) {
	int idOfMid = -1;
	std::vector<glm::vec3>::iterator iter = std::find(resVertices.begin(), resVertices.end(), newVertex);
	if (iter != resVertices.end()) {
		//found the vertex
		idOfMid = std::distance(resVertices.begin(), iter);
	}
	else {
		//have to add the vertex
		resVertices.push_back(newVertex);
		idOfMid = resVertices.size() - 1;
	}
	return idOfMid;
}

glm::vec3 ENGINE::UTIL::IcosphereGenerator::GetMidpoint(glm::vec3 a, glm::vec3 b)
{

	glm::vec3 midPoint = glm::vec3((a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2);
	//make sure the new point is on the unit sphere
	float length = glm::sqrt(midPoint.x * midPoint.x + midPoint.y * midPoint.y + midPoint.z * midPoint.z);

	return midPoint/length;
}
