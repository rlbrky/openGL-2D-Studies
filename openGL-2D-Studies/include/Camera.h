#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 worldUP;
	float zoom;
public:
	Camera();
	Camera(glm::vec3 startPos, glm::vec3 startUp);
	glm::vec3 getCameraPosition();
	void setCameraPosition(glm::vec3 camPosition);
	glm::mat4 CalculateViewMatrix();
};