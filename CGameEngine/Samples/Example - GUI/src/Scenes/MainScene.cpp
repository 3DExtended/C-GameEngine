#include "MainScene.h"
#include "Engine/Util/Generators/IcosphereGenerator.h"
#include <glm/gtx/transform2.hpp>
#include "Engine/Util/Math.h"
#include "Engine/GUI/FontHandler.h"
#include "Engine/Util/Debug/DebugAction.h"

using namespace ENGINE::GUI;
void MainScene::LoadShaders()
{
	Shader *shader = new Shader("./res/shader/diffuseShader");
	shader = new Shader("./res/shader/text");
}
Text* text;
void MainScene::Start()
{
	//Create GameObject
	FontHandler * font = FontHandler::GetFontHandler("./res/font/Arial Font", "./res/shader/text");
	text = font->AddText("Huhu");
}

float size = 1;
void MainScene::Update()
{
	Action("Test");
	size++;
	if (size >= 500)
		size = 400;
	text->SetTextsize(size);
}

void MainScene::Destroy()
{

}
