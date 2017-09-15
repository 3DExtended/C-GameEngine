#pragma once
#include "../Camera.h"
#include "../Input.h"
#include "../Util/Constants.h"
#include <iostream>

namespace ENGINE {
	class Scene;
	class Camera;
	class GameObject;
	class SceneHandler;

	class Component {
	public:
		Component();

		Scene* GetCurrentScene();

		Camera* GetCurrentCamera();

		GameObject* GetCurrentGameObject();

		GameObject* Instantiate();

		GameObject * Instantiate(const std::string name);

		void ShowMouse(bool showMouse);

		void SetMousePosition(int x, int y);
	private:
		friend class GameObject;

		virtual void Awake() {};
		virtual void Start() {};
		virtual void Update() {};
		virtual void LateUpdate() {};
		virtual void Render() {};
		virtual void Destroy() {};

	protected:
		friend class GameObject;
		GameObject* gameObject;
	};
}