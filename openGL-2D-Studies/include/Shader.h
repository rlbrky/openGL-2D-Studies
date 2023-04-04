#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad.h>

class Shader {
private:
	unsigned int shaderID;

	unsigned int uniformColor, uniformMtxTransform, uniformModel, uniformView, uniformProj;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(unsigned int program, const char* shaderCode, GLenum shaderType);
public:
	Shader();
	std::string ReadFile(const char* fileLocation);
	void CreateFromFiles(const char* vertexLoc, const char* fragmentLoc);

	void UseShader();
	void ClearShader();

	void SetUniformColor(glm::vec4 color);
	void SetUniformMatrixTransform(glm::mat3 transform);
	void SetUniformMtx4(std::string name, glm::mat4 matrix);

	unsigned int GetID();
	~Shader();
};