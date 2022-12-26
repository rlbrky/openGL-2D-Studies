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

	void Build(const VertexTypeList& vertices, const IndexList& indexList);
	void Build(const vec3List& vertices);
	//void Build(const VertexTypeList& vertices);

	int GetIndexCount();
	int GetVertexCount();

	void Activate();
	void Deactivate();
};