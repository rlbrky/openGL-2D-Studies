#include "Transform.h"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <iostream>
Transform::Transform() {
	m_position = glm::vec2(0.0f, 0.0f);
	m_scale = glm::vec2(1.0f, 1.0f);
	m_eulerAngles = glm::vec2(0.0f, 0.0f);
	m_mtxTransform = glm::mat3(1);
}
glm::mat3 Transform::getMatrix() {
	return m_mtxTransform;
}
glm::vec2& Transform::getEulerAngles() {
	return m_eulerAngles;
}
glm::vec2& Transform::getPosition() {
	return m_position;
}
glm::vec2& Transform::getScale()
{
	return m_scale;
}

void Transform::setEulerAngles(const glm::vec2& angles) {
	m_eulerAngles = angles;
	Update();
}
void Transform::setPosition(const glm::vec2& pos) {
	m_position = pos;
	Update();
}
void Transform::setScale(const glm::vec2& scale)
{
	m_scale = scale;
	Update();
}

void Transform::Update()
{
	glm::mat3 mtxTranslate = glm::translate(glm::mat3(1), m_position);
	glm::mat3 mtxScale = glm::scale(glm::mat3(1), m_scale);

	//zyx sýrasýyla hesaplayacaðýz

	glm::mat3 mtxRot = glm::rotate(glm::mat3(1),
																glm::radians(m_eulerAngles.x));
	//TRS - Translate - Rotate - Scale sýrasýna göre çarpma iþlemlerini yapýyoruz.

	m_mtxTransform = mtxTranslate* mtxRot* mtxScale;
}