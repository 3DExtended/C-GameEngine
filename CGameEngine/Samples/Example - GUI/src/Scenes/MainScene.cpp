#include "MainScene.h"
#include "Engine/Util/Generators/IcosphereGenerator.h"
#include <glm/gtx/transform2.hpp>
#include "Engine/Util/Math.h"

void MainScene::LoadShaders()
{
	Shader *shader = new Shader("./res/shader/diffuseShader");
	shader = new Shader("./res/shader/TextShader/text");
}

void MainScene::Start()
{
	//Create GameObject
	GameObject * triangle = Instatiate();
	

}

void MainScene::Update()
{

}

void MainScene::Destroy()
{

}
