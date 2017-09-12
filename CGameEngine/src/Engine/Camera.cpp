#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(glm::vec3 pos, float fov, float aspect, float zNear, float zFar)
{
	this->pos = pos;
	this->forward = glm::vec3(0, 0, -1);
	this->up = glm::vec3(0, 1, 0);
	this->projection = glm::perspective(fov, aspect, zNear, zFar);
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return projection;
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(pos, pos + forward, up);
}
