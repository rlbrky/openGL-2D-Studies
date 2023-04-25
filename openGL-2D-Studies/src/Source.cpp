#define GLM_ENABLE_EXPERIMENTAL

#include <glad.h>
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "MeshManager.h"
#include "SetupHandler.h"

#define WIDTH 800
#define HEIGHT 800

SetupHandler* setupHandler;

Scene* scene;

int main() {
	setupHandler = new SetupHandler();
	setupHandler->Build(WIDTH, HEIGHT);

	scene = new Scene(setupHandler->GetWindowPtr());
	MeshManager* manager = scene->getMeshManager();

	setupHandler->SetUI(scene->GetUI());

	setupHandler->AddRenderFunction(std::bind(&Scene::Update, scene));
	setupHandler->AddRenderFunction(std::bind(&Scene::Draw, scene));

	setupHandler->BeginRenderLoop();
		
	glfwTerminate();
	return 0;
}