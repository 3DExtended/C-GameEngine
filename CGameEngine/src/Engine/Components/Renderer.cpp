#include "Renderer.h"
#include "../ComponentBased/GameObject.h"
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
	GLint matrix = shader->getUniform("matrix");
	GLint normal = shader->getUniform("nmatrix");
	GLint pmatrix = shader->getUniform("pmatrix");

	Camera* cam = GetCurrentCamera();

	//calculate uniforms and push them
	glm::mat4 modelMatrix = GetCurrentGameObject()->transform.GetModelMatrix();

	glm::mat4 mat = cam->GetProjectionMatrix() * cam->GetViewMatrix() * modelMatrix; 
	glUniformMatrix4fv(matrix, 1, GL_FALSE, glm::value_ptr(mat));

	//normal matrix
	glm::mat4 norm = glm::transpose(glm::inverse(cam->GetViewMatrix() * modelMatrix));
	glUniformMatrix4fv(normal, 1, GL_FALSE, glm::value_ptr(norm));

	//pMatrix
	glm::mat4 pmat = cam->GetViewMatrix() * modelMatrix;
	glUniformMatrix4fv(pmatrix, 1, GL_FALSE, glm::value_ptr(pmat));

	model->Render();
}
