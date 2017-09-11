#pragma once
#include "Scene.h"
#include "ComponentBased/Component.h"
#include "ComponentBased/GameObject.h"
#include <vector>
#include <iostream>

class Scene;
class GameObject;
class Component;

class SceneHandler {
public:
	static SceneHandler* getInstance();
	~SceneHandler();
	void SwitchScene(uint16_t index);
	void AddScene(Scene* newScene);

private:
	static SceneHandler* instance;
	std::vector<Scene*> scenes;
	SceneHandler();

	Scene* curScene = nullptr;

private:
	friend class ENGINE::EngineClass;
	void Start();
	void Update();
	void Render();

};