#include "SceneHandler.h"

using namespace ENGINE;

ENGINE::SceneHandler* ENGINE::SceneHandler::instance = nullptr;

SceneHandler * SceneHandler::getInstance()
{
	if (instance == nullptr)
		instance = new SceneHandler();
	return instance;
}

SceneHandler::~SceneHandler()
{
}

void SceneHandler::SwitchScene(uint16_t index)
{
	if (curScene == nullptr && scenes.size() == 0) {
		std::cerr << "There are no scenes to switch to.." << std::endl;
	}
	else if (index >= scenes.size()) {
		std::cerr << "The scene you want to switch to is not registered." << std::endl;
	}
	else {
		//clean up current scene
		if (curScene != nullptr) {
			curScene->GameObjectDestroy();
			curScene->Destroy();
			//clean up shaders
		}
		curScene = scenes.at(index);
		Start();
	}
}

void SceneHandler::AddScene(Scene * newScene)
{
	scenes.push_back(newScene);
}

SceneHandler::SceneHandler()
{
}

void SceneHandler::Start()
{
	curScene->LoadShaders();
	curScene->Start();
	curScene->GameObjectAwake();
	curScene->GameObjectStart();
}

void SceneHandler::Update()
{
	curScene->Update();
	curScene->GameObjectUpdate();
	curScene->GameObjectLateUpdate();
}

void SceneHandler::Render()
{
	curScene->GameObjectRender();
}
