#pragma once
#include "../Camera.h"

namespace ENGINE {
	class Scene;
	class Camera;
	class GameObject;
	class SceneHandler;

	class Component {
	public:
		Component();

		Scene* GetCurrentScene();

		Camera* GetCurrentCam();

		GameObject* GetCurrentGameObject();
	private:
		friend class GameObject;

		virtual void Awake() {};
		virtual void Start() {};
		virtual void Update() {};
		virtual void LateUpdate() {};
		virtual void Render() {};
		virtual void Destroy() {};

	};
}