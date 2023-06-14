#pragma once
#include <functional>
#include<vector>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <UI.h>

class Scene;

typedef std::function<void()> RenderFunction;
typedef std::vector<RenderFunction> RenderFunctionList;

class SetupHandler
{
public:
	SetupHandler();
	bool Build(int width, int height);													//Initialise glfw, glad
	void BeginRenderLoop();																//Call Render functions that was added.

	void AddRenderFunction(RenderFunction function);			//Add Render Function
	
	void SetScene(Scene* scene);
	Scene* GetScene();

	void UpdateBuffer(unsigned int& id, unsigned int offset, void* data, unsigned int size, unsigned int type);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);		//A glfw function template for using mouse informations.
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);							//A glfw function template for mouse scroll activities.
	
	GLFWwindow* GetWindowPtr()const;

	void SetLists();
private:
	RenderFunctionList		m_RenderFunctionList;
	GLFWwindow*				m_Window;
	float									zoom;
	Scene*								m_Scene;
	int										m_Width, m_Height;
	std::vector<glm::vec2>					m_ObjCoordinates;
	std::vector<VertexTypeList>		m_VertexList;
	std::vector<VertexTypeList>		m_WcoordVertices;
	std::vector<std::vector<VertexTypeList>>		m_objNWorldCoord;
	std::vector<unsigned int>				m_VboIDList;
	VertexTypeList									verticesPrev;
	VertexTypeList									verticesLast;
	int															i,j,k;
};