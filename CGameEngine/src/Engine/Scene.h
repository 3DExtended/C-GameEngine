#pragma once
#include <vector>
#include "ComponentBased/Component.h"
#include "ComponentBased/GameObject.h"

class GameObject;
class Component;

namespace ENGINE {

	class Scene {
	public:
		Scene();
		~Scene();

		virtual void Start() {};
		virtual void LoadShaders() {};
		virtual void Update() {};
		virtual void Destroy() {};

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