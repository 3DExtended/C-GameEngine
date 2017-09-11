#include <tchar.h>	//Other entry point for windows
#include "Engine/Engine.h"
#include "Engine/SceneHandler.h"

//include all scenes
#include "Scenes/MainScene.h"
using namespace ENGINE;
int _tmain(int argc, _TCHAR* argv[]) {
	
	//Register all scenes we need
	SceneHandler::getInstance()->AddScene(new MainScene());

	//ENGINE::Run(0);
	ENGINE::EngineClass::RunEngine(0);
	return 0;
}