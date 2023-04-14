#include "WindowTransform.h"

#include "Mesh.h"
#include "MeshManager.h"
#include "SceneNode.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"

#include <iostream>

WindowTransform::WindowTransform(MeshManager* meshManager, SceneNode* root)
{
	triangleCount = 0; circleCount = 0; squareCount = 0;

	m_MeshManager = meshManager;
	m_Root = root;
	m_ActiveNode = m_Root;
	childToBeName = "";
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
	ImGui::Begin("Menu");
	if(ImGui::BeginMenu("Object Creator"))
	{
		//TO DO: Every object should have their own color manipulation. Every object should move on their own.
		if (ImGui::MenuItem("Square"))
		{
			squareCount++;
			std::string name = "Square " + std::to_string(squareCount);
			auto mesh = m_MeshManager->createSquare(0.5);
			SceneNode* squareNode = new SceneNode();
			squareNode->AddMesh(mesh);
			squareNode->SetName(name);
			m_Root->AddChild(squareNode);
			SetActiveNode(squareNode);
		}

		if (ImGui::MenuItem("Triangle"))
		{
			triangleCount++;
			std::string name = "Triangle " + std::to_string(triangleCount);
			auto mesh = m_MeshManager->createTriangle(0.5f);
			SceneNode* triangleNode = new SceneNode();
			triangleNode->AddMesh(mesh);
			triangleNode->SetName(name);
			m_Root->AddChild(triangleNode);
			SetActiveNode(triangleNode);
		}

		if (ImGui::MenuItem("Circle"))
		{
			circleCount++;
			std::string name = "Circle " + std::to_string(circleCount);
			auto mesh = m_MeshManager->createCircle(0.3f, 12);
			SceneNode* circleNode = new SceneNode();
			circleNode->AddMesh(mesh);
			circleNode->SetName(name);
			m_Root->AddChild(circleNode);
			SetActiveNode(circleNode);
		}
		ImGui::EndMenu();
	}
	ImGui::End();
	
	ImGui::Begin("Properties"); //PROPERTIES PANEL
	//Change Name of Object
	std::string	 name = m_ActiveNode->GetName();
	ImGui::InputText("Name", &name);
	m_ActiveNode->SetName(name);
	
	ImGui::Separator();
	//New system that lets you control 1 item at a time.(That item being the selected one.)
	ImGui::SliderFloat("Rotation", &m_ActiveNode->GetTransform()->getEulerAngles().x, 0, 360);
	ImGui::SliderFloat2("Transition", &m_ActiveNode->GetTransform()->getPosition().x, -1, 1);

	ImGui::Separator();
	ImGui::InputText("Enter Child Name", &childToBeName);
	if (ImGui::Button("Set Child"))//TO DO: After this Remove First Node?
	{
		m_ActiveNode->AddChild(m_Root->GetChildByName(childToBeName));
		m_Root->GetChildByName(childToBeName)->SetParent(m_ActiveNode);
		childToBeName = "";
	}

	ImGui::End();

	ImGui::Begin("Hierarchy"); //Hierarchy panel
	DrawTree(m_Root);
	ImGui::End();
}

void WindowTransform::DrawTree(SceneNode* node)
{
	if (node)
	{
		unsigned int flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		if (node == m_ActiveNode)
		{
			flags |= ImGuiTreeNodeFlags_Selected;
		}
		if (ImGui::TreeNodeEx(node->GetName().c_str(), flags))
		{
			if (ImGui::IsItemActive())
			{
				m_ActiveNode = node;
			}
			for (int i = 0; i < node->GetChildCount(); i++)
			{ //Write sceneNode's childs to panel
				DrawTree(node->GetChild(i));
			}
			ImGui::TreePop();
		}
	}
}


//DRAG DROP FAILED CODE
//Selecting a second node how will that work ?
//Never managed to enter payload section.
/*
	//The moment you grab the object create source
	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) //No flags set bc every node is both source and targets.
	{
		//Set it to carry nodes - BE CAREFUL - Could lead to mistakes.
		ImGui::SetDragDropPayload("Organise_Tree", &m_ActiveNode, sizeof(&m_ActiveNode));
		ImGui::EndDragDropSource();
	}//TO DO: FOR SOME REASON ONLY DRAGGING FROM BELOW IS POSSIBLE

	if (ImGui::BeginDragDropTarget())//Drop procedures.
	{
		std::cout << "PAYLOAD ACCEPTED" << std::endl;
		//if(const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Organise_Tree"))
		// {
		// } //NEED FIX
		//*(SceneNode*)payload->Data
		ImGui::EndDragDropTarget();
	}
*/

//OLD SYSTEM THAT LETS YOU SEE ALL ITEMS.
/*
	Iterate through and create ImGui sliders to manipulate rotation and transition of the selected object.
	for (int i = 0; i < m_ActiveNode->GetChildCount(); i++)
	{
		//To get unique ID's for the same name in ImGui we use Push/Pop ID functions.
		ImGui::PushID(i);
		ImGui::SliderFloat("Rotation", &m_ActiveNode->GetChild(i)->GetTransform()->getEulerAngles().x, 0, 360);
		ImGui::SliderFloat2("Transition", &m_ActiveNode->GetChild(i)->GetTransform()->getPosition().x, -1, 1);
		ImGui::PopID();
	}*/