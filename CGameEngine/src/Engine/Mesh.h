#pragma once
#include <vector>
#include "glm/glm.hpp"

namespace ENGINE {
	class Mesh {
	public:
		Mesh();
		~Mesh();

		/// <summary>
		/// This function adds a new vertex (with needed attributes) to the mesh
		/// </summary>
		/// <param name="vertexPos">the position of the vertex</param>
		/// <param name="vertexNormal">the normal of that vertex</param>
		/// <param name="vertexTexture">the texture coordinate of that vertex (UV)</param>
		/// <param name="vertexColor">the color of the vertex</param>
		/// <returns></returns>
		int addPoint(glm::vec3 vertexPos, glm::vec3 vertexNormal, glm::vec2 vertexTexture, glm::vec4 vertexColor, bool disablePointSharing = false);

		void addTriangle(uint32_t a, uint32_t b, uint32_t c);

		void addTriangleAndRecalcNormals(uint32_t a, uint32_t b, uint32_t c);

		void transformMesh(glm::mat4 transformationMatrix);
	private:
		friend class Model;
		std::vector<float> point;

		std::vector<uint32_t> index;
	};
}