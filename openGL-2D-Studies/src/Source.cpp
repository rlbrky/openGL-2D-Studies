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
#include "SceneNode.h"

#include <vector>

SetupHandler* setupHandler;
Grid* grid;

std::vector<Mesh*> meshList;

glm::vec2 vecMove;

Scene* scene;
Camera camera;
SceneNode* node;

Transform* transform;

unsigned int programID;

/*void CreateShaders() {
	Shader* shader1 = new Shader();
	Shader* shader2 = new Shader();
	shader1->CreateFromFiles(vertexShader, fragmentShader);
	shader2->CreateFromFiles(gridVertexLocation, gridFragmentLocation);
	shaderList.push_back(shader1);
	shaderList.push_back(shader2);
}*/

int main() {
	setupHandler = new SetupHandler();
	setupHandler->Build(800, 800);
	
	camera.setCameraPosition(glm::vec3(3, 3, 3));
	
	//DÝKKAT!

	node = new SceneNode();
	
	scene = new Scene(setupHandler->GetWindowPtr());
	transform = new Transform();
	MeshManager* manager = scene->getMeshManager();
	//scene->Build(setupHandler->GetWindowPtr());
	//BURADAN DEVAM EDÝLECEK.
	//scene->GetWindowTransform()->BindShader();

	/*meshList.push_back(manager->createSquare());
	meshList.push_back(manager->createTriangle());
	meshList.push_back(manager->createCircle(0.3,24));*/
	scene->GetWindowTransform()->setTransform(transform);
	transform->Update();
	setupHandler->AddRenderFunction(std::bind(&Scene::Draw, scene));

	

	setupHandler->BeginRenderLoop();
		
	glfwTerminate();
	return 0;
}

/*

		//SHADER A UNIFORM TRANSFORM EKLENMELÝ BUNUN ÝÇÝN.
		//glm::mat3 Translate = glm::translate(glm::mat3(1.0f),vecMove);
		//Transform = Translate * Rotate;
		//line.setTransform(Transform);
		//glDrawArrays(GL_LINES, 0, line.GetGridIntexCount());

		scene->Draw();


		/*shaderList[0]->SetUniformPositionSetter(glm::vec3(0.5f, 0.3f, 0.0f));
		shaderList[0]->SetUniformColor(glm::vec4(0.5f, 0.5f, 0.0f, 1.0f));
		meshList[1]->Draw();

		shaderList[0]->SetUniformPositionSetter(glm::vec3(0.7f, 0.5f, 0.0f));
		shaderList[0]->SetUniformColor(glm::vec4(1.0f, 0.5f, 0.3f, 1.0f));
		meshList[2]->DrawArray();
		
*/