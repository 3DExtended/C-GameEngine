#pragma once
namespace ENGINE {
	class Component {
	public:
		Component() {};

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