#include "Transform.h"
#include "GameObject.h"
using namespace ENGINE;
glm::mat4 ENGINE::Transform::GetModelMatrix() {
	if (gameObject->GetParent() != nullptr) {
		return GetPosMatrix() * GetRotationMatrix() * GetScaleMatrix() * gameObject->GetParent()->transform.GetModelMatrix();
	}
	else {
		return GetPosMatrix() * GetRotationMatrix() * GetScaleMatrix();
	}
}

glm::mat4 ENGINE::Transform::GetScaleMatrix() {
	return glm::scale(scale);
}

glm::mat4 ENGINE::Transform::GetRotationMatrix() {
	glm::mat4 rotX = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
	glm::mat4 rotY = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
	glm::mat4 rotZ = glm::rotate(rotation.z, glm::vec3(0, 0, 1));

	glm::mat4 rotMat = rotX*rotY*rotZ;

	return rotMat;
}

glm::mat4 ENGINE::Transform::GetPosMatrix() {
	return glm::translate(position);
}
