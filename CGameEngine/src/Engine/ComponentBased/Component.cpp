#include "Component.h"
#include "GameObject.h"
#include "../Scene.h"
#include "../Camera.h"
#include "../SceneHandler.h"
#include "SDL2/SDL.h"
#include "../Display.h"
#include <glm/glm.hpp>

using namespace ENGINE;

Scene * Component::GetCurrentScene() {
	return SceneHandler::getInstance()->GetCurrentScene();
}

Camera * Component::GetCurrentCamera() { 
	return GetCurrentScene()->GetSceneCam();
}

GameObject * Component::GetCurrentGameObject() {
	return GameObject::currentGameObject; 
}

void Component::ShowMouse(bool showMouse)
{
	SDL_ShowCursor(showMouse ? 1 : 0);
}

void Component::SetMousePosition(int x, int y)
{
	Display::GetInstance()->SetMousePosition(x, y);
}

GameObject * ENGINE::Component::Instantiate()
{
	return GetCurrentScene()->Instatiate();
}

GameObject * ENGINE::Component::Instantiate(std::string name)
{
	return GetCurrentScene()->Instatiate();
}
