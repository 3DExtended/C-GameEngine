#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
namespace ENGINE {
	class GameObject;
	class Transform {
	public:
		Transform(glm::vec3 pos = glm::vec3(0), glm::vec3 rot = glm::vec3(0), glm::vec3 scale = glm::vec3(1.0f)) : position(pos), rotation(rot), scale(scale) {}

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