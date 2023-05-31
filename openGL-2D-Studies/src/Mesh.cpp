#include "Mesh.h"
#include "VertexArrayObject.h"
#include<glad.h>

//Can give Shader to this function for shader processes.
void Mesh::Draw() {
	m_Vao->Activate();

	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);

	m_Vao->Deactivate();
}

VertexArrayObject* Mesh::GetVAO()
{
	return m_Vao;
}