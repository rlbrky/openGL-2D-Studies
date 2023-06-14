#include "Transform.h"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <iostream>
#include <glm/gtx/matrix_decompose.hpp>

Transform::Transform() {
	m_position = glm::vec2(0.0f, 0.0f);
	m_scale = glm::vec2(1.0f, 1.0f);
	m_Rotation = glm::vec2(0.0f, 0.0f);
	m_mtxTransform = glm::mat3(1);
	m_Parent = nullptr;
	m_AspectRatio = 1366 / 768;
}
glm::mat3 Transform::getMatrix() {
	return m_mtxTransform;
}
glm::vec2& Transform::getRotation() {
	return m_Rotation;
}
glm::vec2& Transform::getPosition() {
	return m_position;
}
glm::vec2& Transform::getScale()
{
	return m_scale;
}
Transform* Transform::GetParent()
{
	return m_Parent;
}

void Transform::SetParentTransform(Transform* parent)
{
	m_Parent = parent;
}

void Transform::ApplyParent(Transform* parent)
{
	if (parent) // Get values from parent.
	{
		mtxTranslate = glm::translate(mtxTranslate, parent->getPosition());

		mtxScale = glm::scale(mtxScale, parent->getScale());

		mtxRot = glm::rotate(mtxRot, glm::radians(parent->getRotation().x));

		ApplyParent(parent->GetParent());
	}
}

void Transform::SetRotation(const glm::vec2& angles) {
	m_Rotation = angles;
	Update();
}
void Transform::SetPosition(const glm::vec2& pos) {
	m_position = pos;
	Update();
}
void Transform::SetScale(const glm::vec2& scale)
{
	m_scale = scale;
	Update();
}

void Transform::Update()
{
	mtxTranslate = glm::translate(glm::mat3(1), m_position);

	mtxScale = glm::scale(glm::mat3(1), m_scale);
	//mtxScale = glm::scale(mtxScale, glm::vec2(1.0f,  m_AspectRatio));
	//mtxScale = glm::scale(mtxScale, glm::vec2(m_scale.x / m_AspectRatio, 1.0f));

	mtxRot = glm::rotate(glm::mat3(1),glm::radians(m_Rotation.x));

	ApplyParent(m_Parent);

	//Calculate transform in TRS - Translate - Rotate - Scale order.

	m_mtxTransform = mtxTranslate* mtxRot* mtxScale;
}