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
	bool Build(int width, int height);
	void BeginRenderLoop();

	void AddRenderFunction(RenderFunction function);

	GLFWwindow* GetWindowPtr()const;
private:
	RenderFunctionList m_RenderFunctionList;
	GLFWwindow* m_Window;
};