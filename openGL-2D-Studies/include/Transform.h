#pragma once

#include <glm/mat3x3.hpp>
#include <glm/vec3.hpp>

class Transform
{
public:
	Transform();
	glm::mat3 getMatrix();
	glm::vec2& getRotation();
	glm::vec2& getPosition();
	glm::vec2& getScale();
	Transform* GetParent();

	void SetParentTransform(Transform* parent);
	void SetPosition(const glm::vec2& pos);
	void SetScale(const glm::vec2& scale);
	void SetRotation(const glm::vec2& angles);

	void Update();																				//Do calculations that is given to shaders.

protected:
	glm::vec2				m_position;
	glm::vec2				m_scale;
	glm::vec2				m_Rotation;
	glm::mat3				m_mtxTransform;
	Transform*			m_Parent;
};

