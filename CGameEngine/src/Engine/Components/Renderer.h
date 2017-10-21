#pragma once
#include "../ComponentBased/Component.h"
#include "../Model.h"
#include "../Shader.h"
#include <string>
#include <glm/gtc/type_ptr.hpp>

namespace ENGINE {
	/// <summary>
	/// This class is used to Render a specified model with a given shader. 
	/// </summary>
	/// <remarks>
	/// Note that neither the Model nor the Shader can be used without this class and get rendered.
	/// </remarks>
	class Renderer : public Component{
	public:
		/// <summary>
		/// Creates a new Renderer for a passed shader and a given model. 
		/// </summary>
		/// <param name="shaderName">The path to the shader</param>
		/// <param name="model">A pointer to the model you wanna render</param>
		Renderer(const std::string shaderName, Model* model);

		/// <summary>
		/// This function renders the model using the specified shader to the current context. 
		/// </summary>
		void Render();

	private:
		//A pointer to the shader you wanna use
		Shader* shader;

		//The model you want to render
		Model* model;
	};
}