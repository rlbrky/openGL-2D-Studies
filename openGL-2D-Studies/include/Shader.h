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

	unsigned int uniformColor, uniformMtxTransform;

	void CompileShader(const char* vertexCode, const char* fragmentCode);											//Create and prepare shader.
	void AddShader(unsigned int program, const char* shaderCode, GLenum shaderType);					//Fill shader data with glShaderSource and stuff.
public:
	Shader();
	std::string ReadFile(const char* fileLocation);
	void CreateFromFiles(const char* vertexLoc, const char* fragmentLoc);												//Give locations as const char.

	//glUseProgram, glDeleteProgram.
	void UseShader();
	void ClearShader();

	void SetUniformColor(glm::vec4 color);
	void SetUniformMatrixTransform(glm::mat3 transform);																		//Set values of uniformMtxTransform
	//void SetUniformMtx4(std::string name, glm::mat4 matrix);																	//Set a matris 4x4

	unsigned int GetID();

	~Shader();
};