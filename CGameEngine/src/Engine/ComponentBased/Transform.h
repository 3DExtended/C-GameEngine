#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
namespace ENGINE{
	class Transform {
	public:
		Transform(glm::vec3 pos = glm::vec3(0), glm::vec3 rot = glm::vec3(0), glm::vec3 scale = glm::vec3(1.0f)) : position(pos), rotation(rot), scale(scale) {}

		glm::mat4 GetModelMatrix() {
			return GetPosMatrix() * GetRotationMatrix() * GetScaleMatrix();
		}

		glm::mat4 GetScaleMatrix() {
			return glm::scale(scale);
		}
		
		glm::mat4 GetRotationMatrix() {
			glm::mat4 rotX = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
			glm::mat4 rotY = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
			glm::mat4 rotZ = glm::rotate(rotation.z, glm::vec3(0, 0, 1));

			glm::mat4 rotMat = rotX*rotY*rotZ;
			return rotMat;

		}
		
		glm::mat4 GetPosMatrix() {
			return glm::translate(position);
		}

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	private:

	};
}