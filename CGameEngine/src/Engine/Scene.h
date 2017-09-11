#pragma once
#include <vector>
#include "ComponentBased/Component.h"
#include "ComponentBased/GameObject.h"

#include "Mesh.h"
#include "Model.h"
#include "ComponentBased/Component.h"
#include "ComponentBased/GameObject.h"
#include "glm/glm.hpp"

#include "Components/Renderer.h"




namespace ENGINE {

	class GameObject;
	class Component;

	class Scene {
	public:
		Scene();
		~Scene();

		virtual void Start() {};
		virtual void LoadShaders() {};
		virtual void Update() {};
		virtual void Destroy() {};

		GameObject* Instatiate();

	private:
		std::vector<GameObject*> gameObjects;

	private:
		friend class SceneHandler;
		void GameObjectAwake();
		void GameObjectStart();
		void GameObjectUpdate();
		void GameObjectLateUpdate();
		void GameObjectRender();
		void GameObjectDestroy();

	};
}