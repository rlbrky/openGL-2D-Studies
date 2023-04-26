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
	glfwSetWindowUserPointer(m_Window, this);
	m_Width = width;
	m_Height = height;

	if (m_Window == NULL)
	{
		std::cout << "Can not open window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwSetMouseButtonCallback(m_Window, mouse_button_callback);

	//Mouse scroll callback for zoom property.
	glfwSetScrollCallback(m_Window, scroll_callback);

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

void SetupHandler::SetUI(UI* userInterface)
{
	m_UI = userInterface;
}

void SetupHandler::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	SetupHandler* handler = static_cast<SetupHandler*>(glfwGetWindowUserPointer(window));
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		
		//Getting the x and y values in between -1,1 instead of pixel coordinates.
		float x = (2.0f * mouseX) / handler->m_Width - 1.0f;
		float y = 1.0f - (2.0f * mouseY) / handler->m_Height;
		float z = 1.0f;
		
		//Feed this values into VAO? to manipulate object.

		std::cout << "P_Cursor Position at (" << x << " : " << y << std::endl;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		std::cout << "R_Cursor Position at (" << mouseX << " : " << mouseY << std::endl;
		//Change object position
	}
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//if (glfwRawMouseMotionSupported())
	//    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE); //Can make it false for optimization after you are done maybe ?
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void SetupHandler::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	SetupHandler* handler = static_cast<SetupHandler*>(glfwGetWindowUserPointer(window));

	float scrollAmount = 0.125f;
	if (yoffset == 1 && handler->zoom < 1)
		handler->zoom += scrollAmount;
	if (yoffset == -1 && handler->zoom > -1)
		handler->zoom -= scrollAmount;

	if (handler->zoom > 1.0f)
		handler->zoom = 1.0f;
	if (handler->zoom < -1.0f)
		handler->zoom = -1.0f;

	handler->m_UI->SetSceneNodeScale(handler->zoom);
}