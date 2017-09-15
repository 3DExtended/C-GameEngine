#pragma once
#include <vector>
#include "ComponentBased/Component.h"
#include "ComponentBased/GameObject.h"

#include "Mesh.h"
#include "Model.h"
#include "glm/glm.hpp"

#include "Components/Renderer.h"
#include "Camera.h"



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

		GameObject * Instatiate(const std::string name);

		Camera* cam = new Camera(glm::vec3(0, 0, 0), 70.0f, 
			800.0f / 600.0f,	//TODO replace this by window.width / window.height 
			0.1f, 1000.0f);

		Camera* GetSceneCam() { return cam; }

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