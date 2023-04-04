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

Transform* transform;

WindowTransform* tempTransform;
float zoom;

unsigned int programID;

void mouse_callback(GLFWwindow* window, double mouseX, double mouseY);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main() {
	setupHandler = new SetupHandler();
	setupHandler->Build(WIDTH, HEIGHT);

	glfwSetCursorPosCallback(setupHandler->GetWindowPtr(), mouse_callback);
	
	//Mouse scroll callback for zoom property.
	glfwSetScrollCallback(setupHandler->GetWindowPtr(), scroll_callback);

	scene = new Scene(setupHandler->GetWindowPtr());
	transform = new Transform();
	MeshManager* manager = scene->getMeshManager();

	tempTransform = scene->GetWindowTransform();

	scene->GetWindowTransform()->setTransform(transform);

	setupHandler->AddRenderFunction(std::bind(&Scene::Draw, scene));

	

	setupHandler->BeginRenderLoop();
		
	glfwTerminate();
	return 0;
}

void mouse_callback(GLFWwindow* window, double mouseX, double mouseY)
{
	//if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		glfwGetCursorPos(window, &mouseX, &mouseY);
		std::cout << "Cursor Position at (" << mouseX << " : " << mouseY << std::endl;
	

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