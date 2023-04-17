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
	glm::mat3 mtxTranslate = glm::translate(glm::mat3(1), m_position);

	glm::mat3 mtxScale = glm::scale(glm::mat3(1), m_scale);

	//We will calculate in zyx order.

	glm::mat3 mtxRot = glm::rotate(glm::mat3(1),
																glm::radians(m_Rotation.x));

	if (m_Parent) // Get values from parent. AÞAÐIDAKÝ KODU RECURSIVE YAP.
	{
		mtxTranslate = glm::translate(mtxTranslate, m_Parent->getPosition());

		mtxScale = glm::scale(mtxScale, m_Parent->getScale());

		mtxRot = glm::rotate(mtxRot, glm::radians(m_Parent->getRotation().x));
		if (auto grandParent = m_Parent->GetParent())
		{
			mtxTranslate = glm::translate(mtxTranslate, grandParent->getPosition());

			mtxScale = glm::scale(mtxScale, grandParent->getScale());

			mtxRot = glm::rotate(mtxRot, glm::radians(grandParent->getRotation().x));
		}
	}

	//Calculate transform in TRS - Translate - Rotate - Scale order.

	m_mtxTransform = mtxTranslate* mtxRot* mtxScale;
}