#include "MeshManager.h"
#include "VertexArrayObject.h"
#include "VertexTypes.h"
#include "Mesh.h"
#include "VAOManager.h"
#include <glm/trigonometric.hpp>



MeshManager::MeshManager(VAOManager* vaoManager) {
	m_VaoManager = vaoManager;
}

Mesh* MeshManager::createSquare() {
	
	if (!m_VaoManager->GetVAO("square"))
	{
		float length = 1.0f;
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

Mesh* MeshManager::createTriangle() {

	if (!m_VaoManager->GetVAO("triangle"))
	{
		float length = 1.0f;

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

//??????
Mesh* MeshManager::createCircle(float radius, int pointCount) {
	if (!m_VaoManager->GetVAO("circle"))
	{
		vec3List vertexList;

		std::vector<glm::vec3> tempVertices;
		float angle = 360.0f / pointCount;
		int triangleCount = pointCount - 2;

		for (int i = 0; i < pointCount; i++) {
			float newAngle = angle * i;

			float x = radius * cos(glm::radians(newAngle));
			float y = radius * sin(glm::radians(newAngle));
			float z = 0.0f;

			tempVertices.push_back(glm::vec3(x, y, z));
		}

		for (int i = 0; i < triangleCount; i++) {
			vertexList.push_back(tempVertices[0]);
			vertexList.push_back(tempVertices[i+1]);
			vertexList.push_back(tempVertices[i+2]);
		}

		VertexArrayObject* vao = new VertexArrayObject();
		vao->Build(vertexList);
		m_VaoManager->AddNewObject("circle", vao);
	}
	Mesh* mesh = new Mesh();
	mesh->m_Vao = m_VaoManager->GetVAO("circle");
	mesh->m_IndexCount = mesh->m_Vao->GetIndexCount();
	return mesh;
}