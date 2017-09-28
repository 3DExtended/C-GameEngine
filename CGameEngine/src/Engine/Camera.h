#pragma once
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
namespace ENGINE {
	class Camera {
	public:
		Camera();
		Camera(glm::vec3 pos, float fov, float aspect, float zNear, float zFar);


		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();

		glm::vec3 pos;
		glm::vec3 forward;
		glm::vec3 up;

		float pitch, yaw;

	private:
		glm::mat4 projection;

	};
}