#include "Mesh.h"
#include "VertexArrayObject.h"
#include<glad.h>

void Mesh::Draw() {
	m_Vao->Activate();

	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, m_IndexCount);

	m_Vao->Deactivate();
}

void Mesh::DrawArray() {
	m_Vao->Activate();

	glDrawArrays(GL_TRIANGLES, 0, m_IndexCount);

	m_Vao->Deactivate();
}