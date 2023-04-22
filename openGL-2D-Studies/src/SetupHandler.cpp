#include "SetupHandler.h"
#include <iostream>

SetupHandler::SetupHandler()
{
	m_Window = nullptr;
}

GLFWwindow* SetupHandler::GetWindowPtr()const
{
	return m_Window;
}

bool SetupHandler::Build(int width, int height)
{
	if (!glfwInit())
		return 0;

	m_Window = glfwCreateWindow(width, height, "MyWindow", NULL, NULL);
	if (m_Window == NULL)
	{
		std::cout << "Can not open window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_Window);

	//Checking if GLAD is working correctly.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	return true;
}

void SetupHandler::AddRenderFunction(RenderFunction function)
{
	m_RenderFunctionList.push_back(function);
}

void SetupHandler::BeginRenderLoop()
{
	while (!glfwWindowShouldClose(m_Window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for (auto& nextFunction : m_RenderFunctionList)
		{
			nextFunction();
		}

		glfwSwapBuffers(m_Window);

		glfwPollEvents();
	}
}