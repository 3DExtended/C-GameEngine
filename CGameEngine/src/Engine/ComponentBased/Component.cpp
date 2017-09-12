#include "Component.h"
#include "GameObject.h"
#include "../Scene.h"
#include "../Camera.h"
#include "../SceneHandler.h"


using namespace ENGINE;

Component::Component() {
}

Scene * Component::GetCurrentScene() {
	return SceneHandler::getInstance()->GetCurrentScene();
}

Camera * Component::GetCurrentCam() { 
	return GetCurrentScene()->GetSceneCam();
}

GameObject * Component::GetCurrentGameObject() {
	return GameObject::currentGameObject; 
}
