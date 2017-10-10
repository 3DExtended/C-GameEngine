#pragma once
#include <vector>
#include <string>
#include "Transform.h"
#include "Component.h"
namespace ENGINE {
	/// <summary>
	/// A gameobject is a object in the scene.
	/// It is used as a collection of components with some additional funcionallity:
	/// Each GameObject has a transform component which is used to store the position,
	/// the rotation and the scale of that object. 
	/// GameObjects are also used to handle a parent-child relation of objects (for example useful to make a player object with different attatchments).
	/// </summary>
	/// <remarks>
	/// Note that not every GameObject has to be visible and support some kind of renderer. It can also be used to create handlers or some other singletons. 
	/// </remarks>
	class GameObject {
	public:

		/// <summary>
		/// This creates a new GameObject with the empty string as name.
		/// </summary>
		/// <remarks>
		/// Note that it is strongly advised to create a GameObject using the Instantiate() method offered by the Scene or the component class.
		/// </remarks>
		GameObject();

		/// <summary>
		/// This creates a new GameObject with a specified name.
		/// </summary>
		/// <param name="name">The name of the new GameObject</param>
		/// <remarks>
		/// Note that it is strongly advised to create a GameObject using the Instantiate() method offered by the Scene or the component class.
		/// </remarks>
		GameObject(const std::string name);

		/// <summary>
		/// This method is used to assign a component to the GameObject. 
		/// Note that you have to create a lasting component (using the 'new' macro).
		/// </summary>
		/// <example>
		/// <code>
		///	Component *comp = new RotateObjectComponent();
		/// gameObject->AddComponent(comp);
		/// </code>
		/// </example>
		/// <param name="comp">The component you want to add.</param>
		void AddComponent(Component* comp);

		/// <summary>
		/// The Transform component is assigned to each GameObject to store position scale and rotation.
		/// </summary>
		///	<remarks>
		/// Note that the Parent-Child-relation has impact on the calculations taking place in the transform instance.
		/// </remarks>
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