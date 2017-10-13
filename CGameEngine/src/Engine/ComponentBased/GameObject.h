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
	/// Note that not every GameObject has to be visible and support some kind of render. It can also be used to create handlers or some other singletons. 
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
		GameObject(std::string name);

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

		/// <summary>
		/// This function returns the parent if existing. 
		/// If not existing, this returns nullptr.
		/// </summary>
		/// <returns>The parent gameObject if existing, else nullptr</returns>
		GameObject* GetParent();

		/// <summary>
		/// This returns a list of all child gameobjects that are assigned to this gameObject.
		/// </summary>
		/// <returns>A list of all childs, or an empty list</returns>
		std::vector<GameObject*> GetChilds();

		/// <summary>
		/// Sets the parent for this gameObject
		/// </summary>
		/// <param name="obj">the parent for this object</param>
		void SetParent(GameObject* obj);

		/// <summary>
		/// Adds a child to this gameObject
		/// </summary>
		/// <param name="obj">The new child</param>
		void AddChild(GameObject* obj);
	private:
		//The list of components for this gameObject
		std::vector<Component*> components;

		friend class Scene; //The Scene is the one class that is allowed to call the following functions
		
		// Calls the Awake function on each GameObjects
		void Awake();
		
		// Calls the Start function on each GameObjects
		void Start();

		// Calls the Update function on each GameObjects
		void Update();

		// Calls the LateUpdate function on each GameObjects
		void LateUpdate();

		// Calls the Render function on each GameObjects
		void Render();

		// Calls the Destroy function on each GameObjects
		void Destroy();

		//The name of the gameObject
		const std::string name = "";

		//A pointer to the parent of this gameObject
		GameObject* parent = nullptr;

		//A list of gameobjects representing the childs
		std::vector<GameObject*> childs = std::vector<GameObject*>();

	private:
		friend class Component;	//A Component is allowed to access the currentGameObject to get a reference to it

		//A pointer to the current gameObject 
		static GameObject* currentGameObject;
	};
}