#pragma once
#include "Mesh.h"
#include <GL/glew.h>

namespace ENGINE {
	class Model {
	public:

		Model(Mesh* mesh);
		~Model();

		void Render();

	private:
		GLuint index;
		GLuint vao;
		GLuint point;

		uint32_t size;
	};
}