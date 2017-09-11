#pragma once
#include "Scene.h"
#include "ComponentBased/Component.h"
#include "ComponentBased/GameObject.h"
#include <vector>
#include <iostream>


namespace ENGINE {
	class GameObject;
	class Component;

	class EngineClass;


	class SceneHandler {
	public:
		static SceneHandler* getInstance();
		static void AddScene(Scene* newScene) { getInstance()->_AddScene(newScene); }
		~SceneHandler();
		void SwitchScene(uint16_t index);
		void _AddScene(Scene* newScene);

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
}
