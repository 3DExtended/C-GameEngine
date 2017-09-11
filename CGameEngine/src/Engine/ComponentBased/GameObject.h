#pragma once
#include <vector>
#include <string>
#include "Component.h"

namespace ENGINE {
	class GameObject {
	public:
		GameObject();
		GameObject(const std::string name);

		~GameObject();

		void AddComponent(Component* comp);

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
	};
}