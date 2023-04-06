#include "MeshManager.h"
#include "VertexArrayObject.h"
#include "VertexTypes.h"
#include "Mesh.h"
#include "VAOManager.h"
#include <glm/trigonometric.hpp>



MeshManager::MeshManager(VAOManager* vaoManager) {
	m_VaoManager = vaoManager;
}

Mesh* MeshManager::createSquare(float length) {
	
	if (!m_VaoManager->GetVAO("square"))
	{
		VertexTypeList vertexList = {
		-length / 2, -length / 2, 1.0f, //left bottom point 0
		length / 2, -length / 2, 1.0f, // right bottom point 1 
		-length / 2, length / 2, 1.0f, //left top point 2 
		length / 2, length / 2, 1.0f // right top 3
		};

		//Mapping our square
		IndexList indexList = {
			0, 1, 2, //left bottom point
			3, 1, 2, // right bottom point
		};
		VertexArrayObject* vao = new VertexArrayObject();
		vao->Build(vertexList, indexList);
		m_VaoManager->AddNewObject("square", vao);
	}

	Mesh* mesh = new Mesh();
	mesh->m_Vao = m_VaoManager->GetVAO("square");
	mesh->m_IndexCount = mesh->m_Vao->GetIndexCount();

	return mesh;
}

Mesh* MeshManager::createTriangle(float length) {

	if (!m_VaoManager->GetVAO("triangle"))
	{
		VertexTypeList vertices = {
			-length / 2, -length / 2, 1.0f, //left bottom point 0
			length / 2, -length / 2, 1.0f, // right bottom point 1 
			-length / 2, length / 2, 1.0f, //left top point 2 
		};

		//Mapping our triangle
		IndexList indexList = {
			0, 1, 2 //left bottom point
		};

		VertexArrayObject* vao = new VertexArrayObject();
		vao->Build(vertices, indexList);
		m_VaoManager->AddNewObject("triangle", vao);
	}

	
	Mesh* mesh = new Mesh();
	mesh->m_Vao = m_VaoManager->GetVAO("triangle");
	mesh->m_IndexCount = mesh->m_Vao->GetIndexCount();

	return mesh;
}

Mesh* MeshManager::createCircle(float radius, int pointCount) {
	if (!m_VaoManager->GetVAO("circle"))
	{
		IndexList indexList;
		VertexTypeList vertices;

		//Angle between triangles.
		float angle = 360.0f / pointCount;
		int triangleCount = pointCount - 2;

		//Calculating triangle vertices with our angle.
		for (int i = 0; i < pointCount; i++) {
			float newAngle = angle * i;

			float x = radius * cos(glm::radians(newAngle));
			float y = radius * sin(glm::radians(newAngle));
			float z = 0.0f;

			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
		}

		for (int i = 0; i < triangleCount; i++) {
			indexList.push_back(0);
			indexList.push_back(i+1); 
			indexList.push_back(i+2); 
		}

		VertexArrayObject* vao = new VertexArrayObject();
		vao->Build(vertices, indexList);
		m_VaoManager->AddNewObject("circle", vao);
	}

	Mesh* mesh = new Mesh();
	mesh->m_Vao = m_VaoManager->GetVAO("circle");
	mesh->m_IndexCount = mesh->m_Vao->GetIndexCount();
	return mesh;
}