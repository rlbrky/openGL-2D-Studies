#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

#include <glad.h>
#include <GLFW/glfw3.h>

#include "Grid.h"
#include "Camera.h"
#include "MeshManager.h"
#include "Mesh.h"
#include "Scene.h"
#include "WindowTransform.h"
#include "SetupHandler.h"
#include "Transform.h"

#include <vector>

SetupHandler* setupHandler;
Grid* grid;

std::vector<Mesh*> meshList;

glm::vec2 vecMove;

Scene* scene;
Camera camera;

Transform* transform;

unsigned int programID;

void mouse_callback(GLFWwindow* window, double mouseX, double mouseY);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main() {
	setupHandler = new SetupHandler();
	setupHandler->Build(800, 800);
	
	glfwSetCursorPosCallback(setupHandler->GetWindowPtr(), mouse_callback);
	glfwSetScrollCallback(setupHandler->GetWindowPtr(), scroll_callback);

	scene = new Scene(setupHandler->GetWindowPtr());
	transform = new Transform();
	MeshManager* manager = scene->getMeshManager();

	
	scene->GetWindowTransform()->setTransform(transform);
	//transform->Update();
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
	/*camera.setCameraPosition(glm::vec3(0.0f, 0.0f, yoffset));*/
	float scrollAmount = 0.125f;
	//SET CAMERA
}