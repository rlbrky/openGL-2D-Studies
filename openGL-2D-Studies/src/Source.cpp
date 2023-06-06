#define GLM_ENABLE_EXPERIMENTAL

#include <glad.h>
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "SetupHandler.h"

#define WIDTH 800
#define HEIGHT 800

SetupHandler* setupHandler;

Scene* scene;

int main() {
	setupHandler = new SetupHandler();
	setupHandler->Build(WIDTH, HEIGHT);

	scene = new Scene(setupHandler->GetWindowPtr());

	setupHandler->SetScene(scene);
	
	//setupHandler->AddRenderFunction(std::bind(&SetupHandler::SetLists, setupHandler));
	setupHandler->AddRenderFunction(std::bind(&Scene::Update, scene));
	setupHandler->AddRenderFunction(std::bind(&Scene::Draw, scene));

	setupHandler->BeginRenderLoop();
		
	glfwTerminate();
	return 0;
}