#include "MainScene.h"


#include "../Components/Misc/RotateObject.h"
#include "../Components/CameraMovement.h"
#include "../RunOnce/TerrainGeneration.h"


void MainScene::LoadShaders()
{
	Shader *shader = new Shader("./res/shader/diffuseShader");
}

void MainScene::Start()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	TerrainGeneration terrainGen;
	Mesh *mesh = terrainGen.createTerrainMesh(500, 500, 10.0);

	Model* model = new Model(mesh);

	Renderer * renderer = new Renderer("./res/shader/diffuseShader", model);

	//Create GameObject
	GameObject * triangle = Instatiate();
	triangle->AddComponent(renderer);
	triangle->transform.position = glm::vec3(0, -2, -10);
	triangle->transform.scale = glm::vec3(0.5);
	//triangle->AddComponent(new RotateObject());

	triangle->AddComponent(new CameraMovement());

}

void MainScene::Update()
{

}

void MainScene::Destroy()
{

}
