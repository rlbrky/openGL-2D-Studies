#pragma once


class Mesh;
class VAOManager;

class MeshManager
{
private:
	//With the constructor made private this class cannot be made with "new" keyword.
	VAOManager* m_VaoManager;
	int triangleCount, squareCount, circleCount = 0;
public:
	MeshManager(VAOManager* vaoManager);
	Mesh* createSquare(float length);
	Mesh* createTriangle(float length);
	Mesh* createCircle(float radius, int pointCount);
};