#pragma once
#include <functional>
#include<vector>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <UI.h>

typedef std::function<void()> RenderFunction;
typedef std::vector<RenderFunction> RenderFunctionList;

class SetupHandler
{
public:
	SetupHandler();
	bool Build(int width, int height);													//Initialise glfw, glad
	void BeginRenderLoop();																//Call Render functions that was added.

	void AddRenderFunction(RenderFunction function);			//Add Render Function
	
	void SetUI(UI* userInterface);

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);		//A glfw function template for using mouse informations.
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);							//A glfw function template for mouse scroll activities.
	
	GLFWwindow* GetWindowPtr()const;
private:
	RenderFunctionList		m_RenderFunctionList;
	GLFWwindow*				m_Window;
	float									zoom;
	UI*										m_UI;
	int m_Width, m_Height;
};