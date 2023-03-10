#pragma once
#include <vector>

class VertexArrayObject;
class MeshManager;

class Mesh
{
public:
	void Draw();
	void DrawArray();
private:
	VertexArrayObject* m_Vao;
	unsigned int m_IndexCount;

	friend class MeshManager;
};
typedef std::vector<Mesh*> MeshList;