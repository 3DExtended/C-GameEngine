#include "Renderer.h"
using namespace ENGINE;

Renderer::Renderer(const std::string shaderName, Model * model):model(model)
{
	shader = ENGINE::Shader::getShader(shaderName);
	if (shader == nullptr)
		std::cerr << "There is no shader with that name..." << std::endl;

}

void Renderer::Render()
{
	Bind(shader);

	//TODO bind uniforms


	model->Render();
}
