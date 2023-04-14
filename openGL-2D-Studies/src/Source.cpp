#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

#include <glad.h>
#include <GLFW/glfw3.h>

#include "Grid.h"
#include "MeshManager.h"
#include "Mesh.h"
#include "Scene.h"
#include "WindowTransform.h"
#include "SetupHandler.h"
#include "Transform.h"

#include <vector>

#define WIDTH 1024
#define HEIGHT 1024

SetupHandler* setupHandler;
Grid* grid;

std::vector<Mesh*> meshList;

glm::vec2 vecMove;

Scene* scene;

WindowTransform* tempTransform;
float zoom;

unsigned int programID;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main() {
	setupHandler = new SetupHandler();
	setupHandler->Build(WIDTH, HEIGHT);

	//glfwSetMouseButtonCallback(setupHandler->GetWindowPtr(), mouse_button_callback);
	
	//Mouse scroll callback for zoom property.
	glfwSetScrollCallback(setupHandler->GetWindowPtr(), scroll_callback);

	scene = new Scene(setupHandler->GetWindowPtr());
	MeshManager* manager = scene->getMeshManager();

	tempTransform = scene->GetWindowTransform();

	setupHandler->AddRenderFunction(std::bind(&Scene::Update, scene));
	setupHandler->AddRenderFunction(std::bind(&Scene::Draw, scene));

	setupHandler->BeginRenderLoop();
		
	glfwTerminate();
	return 0;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		std::cout << "P_Cursor Position at (" << mouseX << " : " << mouseY << std::endl;
		//Object position
		
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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	float scrollAmount = 0.125f;
	if(yoffset == 1 && zoom < 1)
		zoom += scrollAmount;
	if (yoffset == -1 && zoom > -1)
		zoom -= scrollAmount;

	if (zoom > 1.0f)
		zoom = 1.0f;
	if (zoom < -1.0f)
		zoom = -1.0f;

	tempTransform->SetSceneNodeScale(zoom);
}