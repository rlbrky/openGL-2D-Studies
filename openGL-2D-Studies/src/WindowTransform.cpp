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
	
	ImGui::Begin("Properties"); //PROPERTIES PANEL
	//Change Name of Object
	std::string	 name = m_ActiveNode->GetName();
	ImGui::InputText("Name", &name);
	m_ActiveNode->SetName(name);
	
	ImGui::Separator();
	//New system that lets you control 1 item at a time.(That item being the selected one.)
	ImGui::SliderFloat("Rotation", &m_ActiveNode->GetTransform()->getEulerAngles().x, 0, 360);
	ImGui::SliderFloat2("Transition", &m_ActiveNode->GetTransform()->getPosition().x, -1, 1);
	ImGui::End();

	ImGui::Begin("Hierarchy"); //hierarchy panel
	DrawTree(m_Root);

	//The moment you grab the object create source
	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) //No flags set bc every node is both source and targets.
	{
		//Set it to carry nodes - BE CAREFUL - Could lead to mistakes.
		ImGui::SetDragDropPayload("Organise_Tree", &m_ActiveNode, sizeof(m_ActiveNode), ImGuiCond_Once);
		ImGui::EndDragDropSource();
	}//TO DO: FOR SOME REASON ONLY DRAGGING FROM BELOW IS POSSIBLE

	if (ImGui::BeginDragDropTarget())//Drop procedures. TO DO: NEVER ENTERS HERE ATM ?
	{
		std::cout << "PAYLOAD ACCEPTED" << std::endl;
		//if(const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Organise_Tree"))
		// {
		// } //NEED FIX
		//*(SceneNode*)payload->Data
		ImGui::EndDragDropTarget();
	}

	ImGui::End();
}


//TO DO: FIND A WAY TO FIX ITEM_ACTIVE ISSUE.
void WindowTransform::DrawTree(SceneNode* node)
{
	if (node)
	{
		int i = 0;
		ImGui::PushID(i++); // PLAY WITH THIS TO GET UNIQUE ID'S TO FIX THE ISSUE.
		unsigned int flags = ImGuiTreeNodeFlags_DefaultOpen;
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
		ImGui::PopID();
	}
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