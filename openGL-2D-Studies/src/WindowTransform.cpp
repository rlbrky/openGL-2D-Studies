#include "WindowTransform.h"

#include "Shader.h"
#include "Mesh.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Scene.h"
#include "MeshManager.h"
#include "Transform.h"
#include "SceneNode.h"

WindowTransform::WindowTransform(Scene* scene)
{
	m_scene = scene;
	shader = new Shader();
	BindShader();
	sceneNode = new SceneNode();
	sceneNode->SetName("Sahne");
}

//Can add parameters for different shaders.
void WindowTransform::BindShader() {
	shader->CreateFromFiles(vertexShader, fragmentShader);
}

void WindowTransform::SetSceneNodeScale(float zoom)
{
	sceneNode->GetTransform()->setScale(glm::vec2(zoom, zoom));
}

//Gets called every frame
void WindowTransform::Draw()
{
	sceneNode->Draw(shader);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Hierarchy");
	ImGui::Text(sceneNode->GetName().c_str());
	for (int i = 0; i < sceneNode->GetChildCount(); i++)
	{
		ImGui::Text(sceneNode->GetChild(i)->GetName().c_str());
	}
	ImGui::End();

	ImGui::Begin("Object Creator");

	//TO DO: Every object should have their own color manipulation. Every object should move on their own.
	if (ImGui::Button("Square")) {
		auto& mesh = *m_scene->getMeshManager()->createSquare(0.5f);
		SceneNode* squareNode = new SceneNode();
		transformList.push_back(squareNode->GetTransform());
		squareNode->AddMesh(&mesh);
		squareNode->SetName("Square"); //TO DO: Unique names exp: Square 1-2-3...
		sceneNode->AddChild(squareNode);
	}

	if (ImGui::Button("Triangle")) {
		auto& mesh = *m_scene->getMeshManager()->createTriangle(0.5f);
		SceneNode* triangleNode = new SceneNode();
		transformList.push_back(triangleNode->GetTransform());
		triangleNode->AddMesh(&mesh);
		triangleNode->SetName("Triangle");
		sceneNode->AddChild(triangleNode);
	}
	
	if (ImGui::Button("Circle")) {
		auto& mesh = *m_scene->getMeshManager()->createCircle(0.3f, 36);
		SceneNode* circleNode = new SceneNode();
		transformList.push_back(circleNode->GetTransform());
		circleNode->AddMesh(&mesh);
		circleNode->SetName("Circle");
		sceneNode->AddChild(circleNode);
	}


	//Iterate through transformList and create ImGui sliders to manipulate rotation and transition of the object.
	for (int i = 0; i < transformList.size(); i++)
	{
		auto& iter = transformList[i];
		//To get unique ID's for the same name in ImGui we use Push/Pop ID functions.
		ImGui::PushID(i);
		ImGui::SliderFloat("Rotation", &iter->getEulerAngles().x, 0, 360);
		ImGui::SliderFloat2("Transition", &iter->getPosition().x, -1, 1);
		ImGui::PopID();
	}

	//SLIDERFLOAT--IMGUI -- vec3 olarak de�erleri shadera at.
	ImGui::End();
	ImGui::EndFrame();

	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}