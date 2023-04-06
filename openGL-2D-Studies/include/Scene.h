#pragma once
#include <glad.h>
#include <GLFW/glfw3.h>
#include "Grid.h"

class MeshManager;
class VAOManager;
class WindowTransform;
class GLFWwindow; //CAUTION
class Grid;

class Scene
{
public:
	Scene(GLFWwindow* myWindow);
	void Build(GLFWwindow* myWindow);
	void Draw();

	WindowTransform* GetWindowTransform();
	MeshManager* getMeshManager();
	VAOManager* GetVaoManager();
private:
	Grid grid;
	unsigned int gridVAO;
	MeshManager* m_MeshManager;
	VAOManager* m_VaoManager;
	WindowTransform* m_WindowTransform;
};