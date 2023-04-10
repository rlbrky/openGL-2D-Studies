#include "WindowTransform.h"

#include "Mesh.h"
#include "MeshManager.h"
#include "SceneNode.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"

WindowTransform::WindowTransform(MeshManager* meshManager, SceneNode* root)
{
	m_MeshManager = meshManager;
	m_Root = root;
	m_ActiveNode = m_Root;
}

void WindowTransform::SetSceneNodeScale(float zoom)
{
	m_Root->GetTransform()->SetScale(glm::vec2(zoom, zoom));
}

void WindowTransform::SetActiveNode(SceneNode* node)
{
	m_ActiveNode = node;
}

//Gets called every frame
void WindowTransform::Draw()
{
	ImGui::Begin("Object Creator");
	//TO DO: Every object should have their own color manipulation. Every object should move on their own.
	//SLIDERFLOAT--IMGUI -- vec3 olarak deðerleri shadera at.
	if (ImGui::Button("Square")) {
		auto mesh = m_MeshManager->createSquare(0.5);
		SceneNode* squareNode = new SceneNode();
		squareNode->AddMesh(mesh);
		squareNode->SetName("Square"); //TO DO: Unique names exp: Square 1-2-3...
		m_Root->AddChild(squareNode);
		SetActiveNode(squareNode);
	}

	if (ImGui::Button("Triangle")) {
		auto mesh = m_MeshManager->createTriangle(0.5f);
		SceneNode* triangleNode = new SceneNode();
		triangleNode->AddMesh(mesh);
		triangleNode->SetName("Triangle");
		m_Root->AddChild(triangleNode);
		SetActiveNode(triangleNode);
	}
	
	if (ImGui::Button("Circle")) {
		auto mesh = m_MeshManager->createCircle(0.3f, 12);
		SceneNode* circleNode = new SceneNode();
		circleNode->AddMesh(mesh);
		circleNode->SetName("Circle");
		m_Root->AddChild(circleNode);
		SetActiveNode(circleNode);
	}
	ImGui::End();
	
	ImGui::Begin("Properties");
	//Change Name of Object
	std::string	 name = m_ActiveNode->GetName();
	ImGui::InputText("Name", &name);
	m_ActiveNode->SetName(name);
	
	ImGui::Separator();
	//New system that lets you control 1 item at a time.(That item being the selected one.)
	ImGui::SliderFloat("Rotation", &m_ActiveNode->GetTransform()->getEulerAngles().x, 0, 360);
	ImGui::SliderFloat2("Transition", &m_ActiveNode->GetTransform()->getPosition().x, -1, 1);
	ImGui::End();
}


/* OLD SYSTEM THAT LETS YOU SEE ALL ITEMS.

	Iterate through and create ImGui sliders to manipulate rotation and transition of the selected object.
	for (int i = 0; i < m_ActiveNode->GetChildCount(); i++)
	{
		//To get unique ID's for the same name in ImGui we use Push/Pop ID functions.
		ImGui::PushID(i);
		ImGui::SliderFloat("Rotation", &m_ActiveNode->GetChild(i)->GetTransform()->getEulerAngles().x, 0, 360);
		ImGui::SliderFloat2("Transition", &m_ActiveNode->GetChild(i)->GetTransform()->getPosition().x, -1, 1);
		ImGui::PopID();
	}*/