#include "MainScene.h"
#include "Engine/Util/Generators/IcosphereGenerator.h"
#include <glm/gtx/transform2.hpp>
#include "Engine/Util/Math.h"
#include "Engine/GUI/FontHandler.h"

void MainScene::LoadShaders()
{
	Shader *shader = new Shader("./res/shader/diffuseShader");
	shader = new Shader("./res/shader/text");
}
Text* text;
void MainScene::Start()
{
	//Create GameObject
	FontHandler * font = FontHandler::GetFontHandler("./res/font/Candara", "./res/shader/text");
	text = font->AddText("Huhu");
}

float size = 1;
void MainScene::Update()
{
	size++;
	if (size >= 100)
		size = 1;
	text->SetTextsize(size);
}

void MainScene::Destroy()
{

}
