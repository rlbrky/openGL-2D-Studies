#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

class VertexTypes
{
public:
	float pos;
	//glm::vec2 tex;
};

typedef std::vector<unsigned int> IndexList;
typedef std::vector<glm::vec3> vec3List;
//typedef std::vector<glm::vec2> TexCoordList;
typedef std::vector<float> VertexTypeList;