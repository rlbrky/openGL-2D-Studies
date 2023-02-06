#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
class Transform
{
public:
	Transform();
	glm::mat3 getMatrix();
	glm::vec2& getEulerAngles();
	glm::vec2& getPosition();
	glm::vec2& getScale();

	void setPosition(const glm::vec2& pos);
	void setScale(const glm::vec2& scale);
	void setEulerAngles(const glm::vec2& angles);
	void Update();
protected:
	glm::vec2 m_position;
	glm::vec2 m_scale;
	glm::vec2 m_eulerAngles;
	glm::mat3 m_mtxTransform;
};

