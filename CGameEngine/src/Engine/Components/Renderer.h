#pragma once
#include "../ComponentBased/Component.h"
#include "../Model.h"
#include "../Shader.h"
#include <string>
#include <glm/gtc/type_ptr.hpp>

namespace ENGINE {
	class Renderer : public Component{
	public:
		Renderer(const std::string shaderName, Model* model);

		void Render();

	private:
		Shader* shader;
		Model* model;
	};
}