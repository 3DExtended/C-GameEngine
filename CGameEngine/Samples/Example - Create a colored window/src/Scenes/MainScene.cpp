#include "MainScene.h"


#include "../Components/Misc/RotateObject.h"
#include "../RunOnce/TerrainGeneration.h"

#include "GL\glew.h"

void MainScene::LoadShaders()
{
	Shader *shader = new Shader("./res/shader/diffuseShader");
}

void MainScene::Start()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDisable(GL_CULL_FACE);

	TerrainGeneration terrainGen;
	Mesh *mesh = terrainGen.createTerrainMesh(10, 10, 0.2);

	Model* model = new Model(mesh);

	Renderer * renderer = new Renderer("./res/shader/diffuseShader", model);

	//Create GameObject
	GameObject * triangle = Instatiate();
	triangle->AddComponent(renderer);
	triangle->transform.position = glm::vec3(0, -2, -10);
	triangle->transform.scale = glm::vec3(0.5);
	triangle->AddComponent(new RotateObject());



}

void MainScene::Update()
{

}

void MainScene::Destroy()
{

}
