#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
namespace ENGINE {
	class GameObject;
	/// <summary>
	/// This class is a part of each GameObject which stores rotation position and a three dimensional scale value for the object.
	/// It also provides a methods for creating (for the rendering of the object) the model matrix.  
	/// </summary>
	class Transform {
	public:
		/// <summary>
		/// This creates a new Transform object where position and rotation can be specified (by default they are 0).
		/// This constructor can also be used with a specified scale value (which by default is 1). 
		/// </summary>
		/// <param name="pos">The three dimensional position of the object</param>
		/// <param name="rot">The three dimensional rotation of the object</param>
		/// <param name="scale">The three dimensional scale of the object</param>
		/// <remarks>
		/// Note that this class can be used without a GameObject but will in this case not be used in the scene.
		/// </remarks>
		Transform(glm::vec3 pos = glm::vec3(0), glm::vec3 rot = glm::vec3(0), glm::vec3 scale = glm::vec3(1.0f)) : position(pos), rotation(rot), scale(scale) {}

		/// <summary>
		/// This method returns a model matrix for this transform object. 
		/// Therefore the position matrix the rotation matrix and the scale matrix is multiplied.
		/// The parent transform is used to calculate this matrix (if and only if existing).
		/// </summary>
		/// <returns>Model matrix (with parent transform)</returns>
		glm::mat4 GetModelMatrix();

		glm::mat4 GetScaleMatrix();

		glm::mat4 GetRotationMatrix();

		glm::mat4 GetPosMatrix();

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	private:
		friend class GameObject;
		GameObject* gameObject;
	};
}