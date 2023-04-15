#pragma once

#include "Shader.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>


class Grid { //Creates the grid 
private:
	const char* gridVertexLocation = "Shaders/lineVertexShader.vert";
	const char* gridFragmentLocation = "Shaders/lineFragmentShader.frag";
	unsigned int gridIndexCount , vertexBufferId ,vertexArrayObjectId
 ,indexBufferId;

	//Store vertices
	std::vector<float> vertices;
	
	public:
		Shader* gridShader;
	Grid();
	int createGrid(int segmentCount);
	int GetGridIndexCount();
	//void setTransform(const glm::mat3& transform);
	~Grid();
};