#pragma once
#include <glad.h>
#include <GLFW/glfw3.h>
#include "Grid.h"

class MeshManager;
class VAOManager;
class UI;
class WindowScene;
class GLFWwindow; //CAUTION
class Grid;
class SceneNode;

class Scene
{
public:
	Scene(GLFWwindow* myWindow);
	void Build(GLFWwindow* myWindow); //Create imgui context
	void Draw();
	void DrawGui();							//Open imgui newframe and call draw functions
	void Update();							//Update node
	void CreateShader();					//Creates shader

	UI* GetUI();
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
	UI*										m_UI;
	SceneNode*						m_Root;
};