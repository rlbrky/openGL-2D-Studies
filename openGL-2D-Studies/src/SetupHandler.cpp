#include "SetupHandler.h"

#include "Scene.h"
#include <iostream>

SetupHandler::SetupHandler()
{
	m_Window = nullptr;
}

GLFWwindow* SetupHandler::GetWindowPtr()const
{
	return m_Window;
}

void SetupHandler::SetLists()
{
	m_VertexList = m_Scene->GetUI()->GetVertexList();
	m_VboIDList = m_Scene->GetUI()->GetVboIDList();
	m_ObjCoordinates = m_Scene->GetUI()->GetObjCoordinates();
	i, j, k = -1;
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

void SetupHandler::SetScene(Scene* scene)
{
	m_Scene = scene;
}

Scene* SetupHandler::GetScene()
{
	return m_Scene;
}

void SetupHandler::UpdateBuffer(unsigned int& id, unsigned int offset, void* data, unsigned int size, unsigned int target) {
	glBindBuffer(target, id);
	glBufferSubData(target, offset, size, data);
}

void SetupHandler::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	SetupHandler* handler = static_cast<SetupHandler*>(glfwGetWindowUserPointer(window));

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		handler->m_WcoordVertices.clear();
		handler->m_objNWorldCoord.clear();

		handler->SetLists();

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		
		for (int i = 0; i < handler->m_ObjCoordinates.size(); i++) //Saves local vertex data as world coordinates of vertices
		{
			VertexTypeList tempList;
			for (int j = 0; j < handler->m_VertexList.at(i).size(); j += 3)
			{
				if (handler->m_ObjCoordinates.at(i).x == 0.0f && handler->m_ObjCoordinates.at(i).y == 0.0f)
				{
					tempList.push_back(handler->m_VertexList.at(i).at(j));
					tempList.push_back(handler->m_VertexList.at(i).at(j + 1));
				}
				else if (handler->m_ObjCoordinates.at(i).x == 0.0f && handler->m_ObjCoordinates.at(i).y != 0.0f)
				{
					tempList.push_back(handler->m_VertexList.at(i).at(j));
					tempList.push_back(handler->m_ObjCoordinates.at(i).y * handler->m_VertexList.at(i).at(j + 1));
				}
				else if (handler->m_ObjCoordinates.at(i).x != 0.0f && handler->m_ObjCoordinates.at(i).y == 0.0f)
				{
					tempList.push_back(handler->m_ObjCoordinates.at(i).x * handler->m_VertexList.at(i).at(j));
					tempList.push_back(handler->m_VertexList.at(i).at(j + 1));
				}
				else
				{
					tempList.push_back(handler->m_ObjCoordinates.at(i).x * handler->m_VertexList.at(i).at(j));
					tempList.push_back(handler->m_ObjCoordinates.at(i).y * handler->m_VertexList.at(i).at(j + 1));
				}
				tempList.push_back(1.0f);
				handler->m_WcoordVertices.push_back(tempList);
			}
			handler->m_objNWorldCoord.push_back(handler->m_WcoordVertices);
		}

		//Getting the x and y values in between -1,1 instead of pixel coordinates.
		float x = (2.0f * mouseX) / handler->m_Width - 1.0f;
		float y = 1.0f - (2.0f * mouseY) / handler->m_Height;
		float z = 1.0f; 

		for (int i = 0; i < handler->m_objNWorldCoord.size(); i++)
		{
			for (int j = 0; j < handler->m_WcoordVertices.size() ; j++)
			{
				if (!handler->m_WcoordVertices.empty() && !handler->m_WcoordVertices.at(j).empty())
				{
					for (int k = 0;k < handler->m_WcoordVertices.at(j).size(); k+=3)
					{
						if (x >= (handler->m_WcoordVertices.at(j).at(k) - 0.05f) && x <= (handler->m_WcoordVertices.at(j).at(k) + 0.05f)
							&& y >= (handler->m_WcoordVertices.at(j).at(k+1) - 0.05f)
							&& y <= (handler->m_WcoordVertices.at(j).at(k+1) + 0.05f))
						{
							std::cout << "Vertex saved " << i << std::endl;
							handler->i = i;
							handler->j = j;
							handler->k = k;
						}
					}
				}
			}
		}
		std::cout << "P_Cursor Position at (" << x << " : " << y << std::endl;
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		std::cout << "R_Cursor Position at (" << mouseX << " : " << mouseY << std::endl; 

		float x = (2.0f * mouseX) / handler->m_Width - 1.0f;
		float y = 1.0f - (2.0f * mouseY) / handler->m_Height;
		float z = 1.0f;
		if (!handler->m_WcoordVertices.empty() && handler->i != -1 && handler->j != -1 && handler->k != -1)
		{
			if (!handler->m_WcoordVertices.at(handler->j).empty() && !handler->m_objNWorldCoord.at(handler->i).empty())
			{
				handler->m_WcoordVertices.at(handler->j).at(handler->k) = x;
				handler->m_WcoordVertices.at(handler->j).at(handler->k + 1) = y;

				/*std::cout << "I : " << handler->i << std::endl;
				std::cout << "J : " << handler->j << std::endl;
				std::cout << "K : " << handler->k << std::endl;*/

				handler->UpdateBuffer(handler->m_VboIDList.at(handler->i), 0, &handler->m_WcoordVertices.at(handler->j).at(0), sizeof(VertexTypes) * handler->m_WcoordVertices.at(handler->j).size(), GL_ARRAY_BUFFER);

				handler->i = -1;
				handler->j = -1;
				handler->k = -1;
			}
		}
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

	handler->m_Scene->GetUI()->SetSceneNodeScale(handler->zoom);
}