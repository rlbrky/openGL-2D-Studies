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

void SetupHandler::SetVertexList()
{
	m_VertexList = m_Scene->GetUI()->GetVertexList();
}

void SetupHandler::SetVboIDList()
{
	m_VboIDList = m_Scene->GetUI()->GetVboIDList();
}

void SetupHandler::SetObjCoordinates()
{
	m_ObjCoordinates = m_Scene->GetUI()->GetObjCoordinates();
}

void SetupHandler::SetLists()
{
	SetObjCoordinates();
	SetVboIDList();
	SetVertexList();
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

void SetupHandler::UpdateBuffer(unsigned int& id, unsigned int offset, void* data, unsigned int size, unsigned int type) {
	glBindBuffer(type, id);
	glBufferSubData(type, offset, size, data);
}

void SetupHandler::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	SetupHandler* handler = static_cast<SetupHandler*>(glfwGetWindowUserPointer(window));
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		if (handler->m_VboIDList.size() != handler->prevVboIDListSize)
		{
			handler->m_WcoordVertices.clear();
			handler->prevVboIDListSize = handler->m_VboIDList.size();

			if (!handler->m_ObjCoordinates.empty())
			{
				for (int i = 0; i < handler->m_VboIDList.size(); i++)
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
						else if (handler->m_ObjCoordinates.at(i).x != 0.0f && handler->m_ObjCoordinates.at(i).y != 0.0f)
						{
							tempList.push_back(handler->m_ObjCoordinates.at(i).x * handler->m_VertexList.at(i).at(j));
							tempList.push_back(handler->m_ObjCoordinates.at(i).y * handler->m_VertexList.at(i).at(j + 1));
						}
						tempList.push_back(handler->m_VertexList.at(i).at(j + 2));
					}
					handler->m_WcoordVertices.push_back(tempList);
				}
			}
		}
		
		//Getting the x and y values in between -1,1 instead of pixel coordinates.
		float x = (2.0f * mouseX) / handler->m_Width - 1.0f;
		float y = 1.0f - (2.0f * mouseY) / handler->m_Height;
		float z = 1.0f; 

		for (int i = 0; i < handler->m_WcoordVertices.size() ; i++)
		{
			if (!handler->m_WcoordVertices.empty() && !handler->m_WcoordVertices.at(i).empty())
			{
				for (int j = 0; j < handler->m_WcoordVertices.at(i).size(); j+=3)
				{
					if (x >= (handler->m_WcoordVertices.at(i).at(j) - 0.05f) && x <= (handler->m_WcoordVertices.at(i).at(j) + 0.05f)
						&& y >= (handler->m_WcoordVertices.at(i).at(j+1) - 0.05f)
						&& y <= (handler->m_WcoordVertices.at(i).at(j+1) + 0.05f))
					{
						handler->verticesPrev = handler->m_WcoordVertices.at(i);
						handler->j = j;
					}
				}
			}
		}
		//handler->UpdateBuffer(); -> this should be called with data and buffer id.


		std::cout << "P_Cursor Position at (" << x << " : " << y << std::endl;
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		std::cout << "R_Cursor Position at (" << mouseX << " : " << mouseY << std::endl; //FARENIN SON KOORDÝNATI KULLANILIR VE VERTEXLER YENÝDEN HESAPLANIR.

		float x = (2.0f * mouseX) / handler->m_Width - 1.0f;
		float y = 1.0f - (2.0f * mouseY) / handler->m_Height;
		float z = 1.0f;

		if (!handler->verticesPrev.empty())
		{
			handler->verticesPrev.at(handler->j) = x;
			handler->verticesPrev.at(handler->j + 1) = y;

			handler->verticesLast = handler->verticesPrev;

			handler->UpdateBuffer(handler->m_VboIDList.at(handler->i), 0, &handler->verticesLast[0], sizeof(VertexTypes) * handler->verticesLast.size(), GL_ARRAY_BUFFER);
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