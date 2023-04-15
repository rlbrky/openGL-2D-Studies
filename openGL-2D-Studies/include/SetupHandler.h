#pragma once
#include <functional>
#include<vector>
#include <glad.h>
#include <GLFW/glfw3.h>

typedef std::function<void()> RenderFunction;
typedef std::vector<RenderFunction> RenderFunctionList;

class SetupHandler
{
public:
	SetupHandler();
	bool Build(int width, int height);													//Initialise glfw, glad
	void BeginRenderLoop();																//Call Render functions that was added.

	void AddRenderFunction(RenderFunction function);			//Add Render Function

	GLFWwindow* GetWindowPtr()const;
private:
	RenderFunctionList m_RenderFunctionList;
	GLFWwindow* m_Window;
};