#include "Camera.h"

Camera::Camera() {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	worldUP = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, 0.1f, 100.0f);
}

//Camera(fov, width, height)

Camera::Camera(glm::vec3 startPos, glm::vec3 startUp) {
	position = startPos;
	worldUP = startUp;

	front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, 0.1f, 100.0f);
}

void Camera::setCameraPosition(glm::vec3 camPosition) {
	position = camPosition;
}

glm::vec3 Camera::getCameraPosition() {
	return position;
}

glm::mat4 Camera::CalculateViewMatrix() {
	return glm::lookAt(position, position + front, up);
}