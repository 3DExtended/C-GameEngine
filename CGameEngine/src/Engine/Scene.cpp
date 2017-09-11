#include "Scene.h"

Scene::Scene()
{
	//TODO maybe create a default camera 
}

Scene::~Scene()
{
}

void Scene::GameObjectAwake()
{
	for (GameObject* go : gameObjects) {
		go->Awake();
	}
}

void Scene::GameObjectStart()
{
	for (GameObject* go : gameObjects) {
		go->Start();
	}
}

void Scene::GameObjectUpdate()
{
	for (GameObject* go : gameObjects) {
		go->Update();
	}
}

void Scene::GameObjectLateUpdate()
{
	for (GameObject* go : gameObjects) {
		go->LateUpdate();
	}
}

void Scene::GameObjectRender()
{
	for (GameObject* go : gameObjects) {
		go->Render();
	}
}

void Scene::GameObjectDestroy()
{
	for (GameObject* go : gameObjects) {
		go->Destroy();
	}
}
