#pragma once


class Mesh;
class VAOManager;

class MeshManager
{
private:
	//With the constructor made private this class cannot be made with "new" keyword.
	VAOManager* m_VaoManager;
public:
	MeshManager(VAOManager* vaoManager);
	Mesh* createSquare();
	Mesh* createTriangle();
	Mesh* createCircle(float radius, int pointCount);
};