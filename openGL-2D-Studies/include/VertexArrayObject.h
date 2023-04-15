#pragma once
#include "VertexTypes.h"
class VertexArrayObject
{
private:
	unsigned int m_VboID;
	unsigned int m_IboID;
	unsigned int m_VaoID;
	std::vector<unsigned int> m_AttribList;
	unsigned int m_IndexCount;
	unsigned int m_VertexCount;
public:
	VertexArrayObject();
	~VertexArrayObject();

	void Build(const VertexTypeList& vertices, const IndexList& indexList);			//Standart Opengl pipeline with VAO, VBO, IBO

	int GetIndexCount();
	int GetVertexCount();

	void Activate();																														//Bind vertexArray and VertexAttribArray
	void Deactivate();
};