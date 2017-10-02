#include "Mesh.h"
#include <iostream>

using namespace ENGINE;
Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

int Mesh::addPoint(glm::vec3 vertexPos, glm::vec3 vertexNormal, glm::vec2 vertexTexture, glm::vec4 vertexColor, bool disablePointSharing)
{
	//first check if we already have this set of information
	uint32_t i = 0;
	while (!disablePointSharing && i < (uint32_t)point.size()) {
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

void Mesh::addTriangleAndRecalcNormals(uint32_t a, uint32_t b, uint32_t c)
{
	index.push_back(a);
	index.push_back(b);
	index.push_back(c);

	glm::vec3 posA = glm::vec3(point[a * 12 + 0], point[a * 12 + 1], point[a * 12 + 2]);
	glm::vec3 posB = glm::vec3(point[b * 12 + 0], point[b * 12 + 1], point[b * 12 + 2]);
	glm::vec3 posC = glm::vec3(point[c * 12 + 0], point[c * 12 + 1], point[c * 12 + 2]);

	glm::vec3 u = posB - posA;
	glm::vec3 v = posC - posA;
	glm::vec3 normal(u.y * v.z - u.z * v.y, u.z*v.x - u.x*v.z, u.x*v.y - u.y*v.x);

	point[a * 12 + 3] = normal.x;
	point[a * 12 + 4] = normal.y;
	point[a * 12 + 5] = normal.z;

	point[b * 12 + 3] = normal.x;
	point[b * 12 + 4] = normal.y;
	point[b * 12 + 5] = normal.z;

	point[c * 12 + 3] = normal.x;
	point[c * 12 + 4] = normal.y;
	point[c * 12 + 5] = normal.z;
}

void Mesh::addTriangleAndRecalcNormalsFlatShader(uint32_t a, uint32_t b, uint32_t c)
{
	index.push_back(a);
	index.push_back(b);
	index.push_back(c);

	glm::vec3 posA = glm::vec3(point[a * 12 + 0], point[a * 12 + 1], point[a * 12 + 2]);
	glm::vec3 posB = glm::vec3(point[b * 12 + 0], point[b * 12 + 1], point[b * 12 + 2]);
	glm::vec3 posC = glm::vec3(point[c * 12 + 0], point[c * 12 + 1], point[c * 12 + 2]);

	glm::vec3 u = posB - posA;
	glm::vec3 v = posC - posA;
	glm::vec3 normal = glm::normalize(glm::vec3(u.y * v.z - u.z * v.y, u.z*v.x - u.x*v.z, u.x*v.y - u.y*v.x));

	point[a * 12 + 3] = normal.x;
	point[a * 12 + 4] = normal.y;
	point[a * 12 + 5] = normal.z;
}

void Mesh::addTriangleAndSetNormalFlatShader(uint32_t a, uint32_t b, uint32_t c, glm::vec3 normal)
{
	index.push_back(a);
	index.push_back(b);
	index.push_back(c);

	point[a * 12 + 3] = normal.x;
	point[a * 12 + 4] = normal.y;
	point[a * 12 + 5] = normal.z;
}

void Mesh::transformMesh(glm::mat4 transformationMatrix)
{
	glm::mat4 normalMatrix = glm::transpose(glm::inverse(transformationMatrix));

	for (unsigned int i = 0; i < point.size(); i+=12) {
		//update positions
		glm::vec4 pos(point[i + 0], point[i + 1], point[i + 2],1.0f);
		pos = transformationMatrix * pos;
		point[i + 0] = pos.x;
		point[i + 1] = pos.y;
		point[i + 2] = pos.z;

		//update normal
		glm::vec4 normal(point[i + 3], point[i + 4], point[i + 5], 0.0f);
		normal = normalMatrix * normal;
		point[i + 3] = normal.x;
		point[i + 4] = normal.y;
		point[i + 5] = normal.z;
	}
}

void Mesh::mergeMesh(Mesh* mesh) {
	unsigned int indexSize = point.size() / 12;

	for (unsigned int i = 0; i < mesh->point.size(); i++) {
		auto tempVec = mesh->point[i];
		point.push_back(tempVec);
	}

	for (unsigned int i = 0; i < mesh->index.size(); i++) {
		index.push_back(mesh->index[i] + indexSize);
	}


}

Mesh * ENGINE::Mesh::LoadObj(const std::string path)
{
	Mesh * res = new Mesh();
	std::size_t found = path.find(".obj");
	if (found != std::string::npos) {
		std::cerr << "Please use the path to the OBJ file without the obj file extension." << std::endl;
		return nullptr;
	}

	std::vector<glm::vec3> vertecies;
	std::vector<glm::vec3> normal;
	std::vector<glm::vec2> texture;
	std::vector<glm::vec4> colors = LoadMTLColors(path);
	
	//Load an obj file
	std::ifstream fileStream((path + ".obj").c_str(), std::ios::in);

	if (fileStream.is_open()) {
		std::string currentLine = "";
		int currentColor = -1;
		while (getline(fileStream, currentLine)) {
			std::vector<std::string> parts = ENGINE::UTIL::splitString(currentLine, ' ');
			if (parts.size() >= 1) {
				if (parts[0].compare("vn") == 0) { //Normals
					normal.push_back(glm::vec3(std::stof(parts[1]), std::stof(parts[2]), std::stof(parts[3])));
				}
				else if (parts[0].compare("vt") == 0) {	//Texture Coords
					texture.push_back(glm::vec2(std::stof(parts[1]), std::stof(parts[2])));
				}
				else if (parts[0].compare("v") == 0) {	//Vertex pos
					vertecies.push_back(glm::vec3(std::stof(parts[1]), std::stof(parts[2]), std::stof(parts[3])));
				}
				else if (parts[0].compare("g") == 0) {	//New object
														//TODO this letter introduces a new Object (probably with a different material set). Handle it
				}
				else if (parts[0].compare("usemtl") == 0) {	//Set the material/color for the next faces
					currentColor++;
				}
				else if (parts[0].compare("f") == 0) {	//Vertex pos
					// v vt vn
					std::vector<std::string> subA = ENGINE::UTIL::splitString(parts[1], '/');
					int a = res->addPoint(
						vertecies[std::stoi(subA[0]) - 1],
						(normal.size() == 0) ? glm::vec3(0) : normal[std::stoi(subA[2]) - 1],
						(texture.size() == 0) ? glm::vec2(0) : texture[std::stoi(subA[1]) - 1], 
						(colors.size() == 0) ? glm::vec4(1) : colors[currentColor]
					);
					
					std::vector<std::string> subB = ENGINE::UTIL::splitString(parts[2], '/');
					int b = res->addPoint(
						vertecies[std::stoi(subB[0]) - 1],
						(normal.size() == 0) ? glm::vec3(0) : normal[std::stoi(subB[2]) - 1],
						(texture.size() == 0) ? glm::vec2(0) : texture[std::stoi(subB[1]) - 1],
						(colors.size() == 0) ? glm::vec4(1) : colors[currentColor]
					);

					std::vector<std::string> subC = ENGINE::UTIL::splitString(parts[3], '/');
					int c = res->addPoint(
						vertecies[std::stoi(subC[0]) - 1],
						(normal.size() == 0) ? glm::vec3(0) : normal[std::stoi(subC[2]) - 1],
						(texture.size() == 0) ? glm::vec2(0) : texture[std::stoi(subC[1]) - 1],
						(colors.size() == 0) ? glm::vec4(1) : colors[currentColor]
					);

					if (normal.size() == 0) {
						res->addTriangleAndRecalcNormals(a, b, c);
					}
					else {
						res->addTriangle(a,b,c);
					}
				}
			}
		}
		fileStream.close();
	}
	else {
		std::cout << "Impossible to open %s. Are you sure you are in the right directory?" << path << std::endl;
		return nullptr;
	}


	return res;
}

std::vector<glm::vec4> ENGINE::Mesh::LoadMTLColors(const std::string path)
{


	std::vector<glm::vec4> colors;

	ENGINE::UTIL::printCurrentWorkingDirectory();

	//Load an obj file
	std::ifstream fileStream((path + ".mtl").c_str(), std::ios::in);

	if (fileStream.is_open()) {
		std::string currentLine = "";
		int currentColor = 0;
		while (getline(fileStream, currentLine)) {
			std::vector<std::string> parts = ENGINE::UTIL::splitString(currentLine, ' ');
			if (parts.size() >= 1) {
				if (parts[0].compare("Kd") == 0) { //reading the color value
					colors.push_back(glm::vec4(std::stof(parts[1]), std::stof(parts[2]), std::stof(parts[3]),1));
				}
			}
		}
	}

	return colors;
}
