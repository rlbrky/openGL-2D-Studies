#pragma once
#include <glad.h>
#include <GLFW/glfw3.h>
#include "Grid.h"

class MeshManager;
class VAOManager;
class WindowTransform;
class WindowScene;
class GLFWwindow; //CAUTION
class Grid;
class SceneNode;

class Scene
{
public:
	Scene(GLFWwindow* myWindow);
	void Build(GLFWwindow* myWindow);
	void Draw();
	void DrawGui();
	void Update();
	void BindShader();
	void AddNodeToScene(SceneNode* newNode);

	WindowTransform* GetWindowTransform();
	MeshManager* getMeshManager();
	VAOManager* GetVaoManager();
private:
	const char* vertexShader = "Shaders/vertexShader.vert";
	const char* fragmentShader = "Shaders/fragmentShader.frag";
	
	Shader*								shader;
	Grid									grid;
	unsigned int					gridVAO;
	MeshManager*				m_MeshManager;
	VAOManager*					m_VaoManager;
	WindowTransform*		m_WindowTransform;
	WindowScene*				m_WindowScene;
	SceneNode*						m_Root;
};