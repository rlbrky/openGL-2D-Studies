#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glad.h>

class Shader {
private:
	unsigned int shaderID;

	unsigned int uniformPosSetter, uniformColor;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(unsigned int program, const char* shaderCode, GLenum shaderType);
public:
	Shader();
	std::string ReadFile(const char* fileLocation);
	void CreateFromFiles(const char* vertexLoc, const char* fragmentLoc);

	void UseShader();
	void ClearShader();

	void SetUniformPositionSetter(glm::vec3 posSet);
	void SetUniformColor(glm::vec4 color);

	unsigned int GetID();
	~Shader();
};