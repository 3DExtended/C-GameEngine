#include "MainScene.h"


#include "../Components/Misc/RotateObject.h"
#include "../Components/CameraMovement.h"
#include "../RunOnce/TerrainGeneration.h"
#include "Engine/Util/Generators/IcosphereGenerator.h"
#include <glm/gtx/transform2.hpp>
#include "Engine/Util/Math.h"

void MainScene::LoadShaders()
{
	Shader *shader = new Shader("./res/shader/diffuseShader");
}

void MainScene::Start()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Create GameObject
	GameObject * triangle = Instatiate();

	TerrainGeneration terrainGen;
	Mesh *mesh = terrainGen.createTerrainMesh(100, 100, 5.0);
	Model* model = new Model(mesh);
	Renderer * renderer = new Renderer("./res/shader/diffuseShader", model);
	triangle->AddComponent(renderer);
	
	Mesh *sphere = IcosphereGenerator::createIcosphere(glm::vec3(1), 1, glm::vec4(128.0f / 255.0f, 156.0f / 255.0f, 82.0f / 255.0f,1));
	sphere->transformMesh(
		glm::translate(glm::vec3(0, 5, 0))*
		//UTIL::shearMatrix(0,-1,0,-1,0,1)
		glm::scale(glm::vec3(5,1,3))
	);
	Model* modelsphere = new Model(sphere);
	renderer = new Renderer("./res/shader/diffuseShader", modelsphere);
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
