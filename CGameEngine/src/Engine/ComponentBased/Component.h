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

	/// <summary>
	/// This class is abstract and has to be inherited.
	/// It provides the standard functions as Start() or Update() and when added to an active GameObject instance is called by the engine.
	/// It also provides basic functionality to the engine like a ShowMouse function.  
	/// </summary>
	class Component {
	public:
		Component() {};

		/// <summary>
		/// Returns a handle to the active scene (to access their functionalities).
		/// </summary>
		/// <returns>A pointer to the active/current scene.</returns>
		Scene* GetCurrentScene();

		/// <summary>
		/// Returns a pointer to the current scene camera. 
		/// Usefull e.g. to update the cameras location or rotation.
		/// </summary>
		/// <returns>A pointer to the current/active camera.</returns>
		Camera* GetCurrentCamera();

		/// <summary>
		/// Returns a pointer to the gameObject the component is running on/connected to.
		/// </summary>
		/// <returns>A pointer to the gameObject.</returns>
		GameObject* GetCurrentGameObject();

		/// <summary>
		/// Creates a new gameObject with name "". 
		/// This GameObject is introduced to the current scene.
		/// </summary>
		/// <returns>A pointer to the empty gameObject.</returns>
		GameObject* Instantiate();

		/// <summary>
		/// Creates a new gameObject with a specified name. 
		/// This GameObject is introduced to the current scene.
		/// </summary>
		/// <param name="name">The name for the new GameObject</param>
		/// <returns>A pointer to the empty gameObject with the name.</returns>
		GameObject * Instantiate(std::string name);

		/// <summary>
		/// Can be used to en-/disable the mouse pointer while the mouse is hovering over the window opened by the Game-Engine.
		/// </summary>
		/// <param name="showMouse">If true the mouse is shown, if false it is not.</param>
		void ShowMouse(bool showMouse);

		/// <summary>
		/// Sets the mouse position relative to the window.
		/// Note that the mouse position can be set when the mouse is not showing.
		/// </summary>
		/// <param name="x">The target mouse position on the X-Axis in pixel.</param>
		/// <param name="y">The target mouse position on the Y-Axis in pixel.</param>
		void SetMousePosition(int x, int y);
	private:
		friend class GameObject;	//So the GameObject can call the component standard functions

		/// <summary>
		/// This function is called in the following frame after the component was created.
		/// Is called BEFORE Start().
		/// </summary>
		virtual void Awake() {};

		/// <summary>
		/// This function is called in the following frame after the component was created 
		/// Is called AFTER Awake().
		/// </summary>
		virtual void Start() {};

		/// <summary>
		/// This function is called each frame to update the component (and/or scene). 
		/// Is called as first update function each frame.
		/// </summary>
		virtual void Update() {};

		/// <summary>
		/// This function is called each frame to update the component (and/or scene). 
		/// Is called AFTER Update().
		/// </summary>
		virtual void LateUpdate() {};

		/// <summary>
		/// This function is called to render the scene (once a frame). 
		/// Is called AFTER LateUpdate().
		/// </summary>
		virtual void Render() {};

		/// <summary>
		/// This function is called when the component gets destroyed.
		/// </summary>
		virtual void Destroy() {};

	protected:
		friend class GameObject;

		//a pointer to the current GameObject
		GameObject* gameObject;		
	};
}