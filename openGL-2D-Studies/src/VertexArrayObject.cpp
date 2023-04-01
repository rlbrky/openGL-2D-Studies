#include "VertexArrayObject.h"
#include <glad.h>

VertexArrayObject::VertexArrayObject() {
	m_VaoID = 0;
	m_VboID = 0;
	m_IboID = 0;
}

void VertexArrayObject::Build(const VertexTypeList& vertices, const IndexList& indices) {
	glGenVertexArrays(1, &m_VaoID);
	glGenBuffers(1, &m_VboID);
	glGenBuffers(1, &m_IboID);

	glBindVertexArray(m_VaoID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
	//Giving the class size multiplied by list size ?
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexTypes) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	//BURADAKÝ 3'e dikkat etmeli.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	glEnableVertexAttribArray(0);

	//Last number tells us that we are skipping 3 float points.
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3*sizeof(float)));

	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	m_AttribList.push_back(0);
	m_AttribList.push_back(1);

	m_IndexCount = indices.size();
}

void VertexArrayObject::Build(const vec3List& vertices) {
	glGenVertexArrays(1, &m_VaoID);
	glGenBuffers(1, &m_VboID);

	glBindVertexArray(m_VaoID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
	//Giving the class size multiplied by list size ?
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	//BURADAKÝ 3'e dikkat etmeli.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	m_AttribList.push_back(0);

	m_VertexCount = vertices.size();
}

void VertexArrayObject::Activate() {
	glBindVertexArray(m_VaoID);
	for (auto next : m_AttribList)
		glEnableVertexAttribArray(next);
}

void VertexArrayObject::Deactivate() {
	for (auto next : m_AttribList)
		glDisableVertexAttribArray(next);
	glBindVertexArray(0);
}

int VertexArrayObject::GetIndexCount() {
	return m_IndexCount;
}

int VertexArrayObject::GetVertexCount() {
	return m_VertexCount;
}

VertexArrayObject::~VertexArrayObject() {
	if (m_VboID)
		glDeleteBuffers(1, &m_VboID);
	if (m_VaoID)
		glDeleteBuffers(1, &m_VaoID);
	if (m_IboID)
		glDeleteBuffers(1, &m_IboID);
}