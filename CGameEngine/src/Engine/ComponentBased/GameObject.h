#pragma once
#include <vector>
#include <string>
#include "Transform.h"
#include "Component.h"
namespace ENGINE {
	class GameObject {
	public:
		GameObject();
		GameObject(const std::string name);

		~GameObject();

		void AddComponent(Component* comp);

		Transform transform;

		GameObject* GetParent();
		std::vector<GameObject*> GetChilds();

		void SetParent(GameObject* obj);
		void AddChild(GameObject* obj);
	private:
		std::vector<Component*> components;

		friend class Scene;
		void Awake();
		void Start();
		void Update();
		void LateUpdate();
		void Render();
		void Destroy();

		const std::string name = "";

		GameObject* parent = nullptr;
		std::vector<GameObject*> childs = std::vector<GameObject*>();

	private:
		friend class Component;
		static GameObject* currentGameObject;
	};
}