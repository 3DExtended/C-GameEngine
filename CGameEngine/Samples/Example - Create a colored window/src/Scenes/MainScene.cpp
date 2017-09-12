#include "MainScene.h"


#include "../Components/Misc/RotateObject.h"

void MainScene::LoadShaders()
{
	Shader *shader = new Shader("./res/shader/diffuseShader");
}

void MainScene::Start()
{
	Mesh *mesh = new Mesh();
	mesh->addPoint(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec2(0, 0), glm::vec4(1, 0, 0, 1));
	mesh->addPoint(glm::vec3(-1, 0, 0), glm::vec3(0, 0, -1), glm::vec2(0, 0), glm::vec4(0, 0, 1, 1));
	mesh->addPoint(glm::vec3(1, -1, 0), glm::vec3(0, 0, -1), glm::vec2(0, 0), glm::vec4(0, 1, 0, 1));

	mesh->addTriangle(0, 1, 2);

	Model* model = new Model(mesh);

	Renderer * renderer = new Renderer("./res/shader/diffuseShader", model);

	//Create GameObject
	GameObject * triangle = Instatiate();
	triangle->AddComponent(renderer);
	triangle->transform.position = glm::vec3(0, 0, -10);
	triangle->transform.scale = glm::vec3(3);
	triangle->AddComponent(new RotateObject());
}

void MainScene::Update()
{

}

void MainScene::Destroy()
{

}
