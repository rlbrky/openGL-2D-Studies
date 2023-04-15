#include "Shader.h"

Shader::Shader() {
	shaderID = 0;
}

void Shader::AddShader(unsigned int program, const char* shaderCode, GLenum shaderType) {
	unsigned int shader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength = strlen(shaderCode);

	glShaderSource(shader, 1, &theCode[0], &codeLength);
	glCompileShader(shader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	//Checking for errors in shader.
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error compiling %d shader: '%s' \n", shaderType, eLog);
		return;
	}

	glAttachShader(program, shader);
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode) {
	shaderID = glCreateProgram();

	if (!shaderID) {
		std::cout << "Error creating shader program!"<<std::endl;
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	//Checking if the program is linked properly.
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: %s \n", eLog);
		return;
	}

	//Checking if we can execute the program or not.
	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: %s \n", eLog);
		return;
	}

	uniformMtxTransform = glGetUniformLocation(shaderID, "uMtxTransform");
	uniformColor = glGetUniformLocation(shaderID, "uColor");
}

void Shader::CreateFromFiles(const char* vertexLoc, const char* fragmentLoc) {
	std::string vertexStr = ReadFile(vertexLoc);
	std::string fragmentStr = ReadFile(fragmentLoc);
	const char* vertexCode = vertexStr.c_str();
	const char* fragmentCode = fragmentStr.c_str();

	CompileShader(vertexCode, fragmentCode);
}

std::string Shader::ReadFile(const char* fileLocation) {
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to read %s! File doesn't exist.", fileLocation);
		return "";
	}
	std::string line;
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::UseShader(){
	glUseProgram(shaderID);
}
void Shader::ClearShader(){
	if (shaderID != 0) {
		glDeleteProgram(shaderID);
		shaderID;
	}

	//Any other reset.
}

unsigned int Shader::GetID() {
	return shaderID;
}

void Shader::SetUniformColor(glm::vec4 color) {
	glUniform4f(uniformColor, color.r, color.g, color.b, color.a);
}

void Shader::SetUniformMatrixTransform(glm::mat3 transform) {
	glUniformMatrix3fv(uniformMtxTransform, 1, GL_FALSE, glm::value_ptr(transform));
}

//void Shader::SetUniformMtx4(std::string name, glm::mat4 matrix)
//{
//	glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
//}

Shader::~Shader() {
	ClearShader();
}