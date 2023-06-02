#include "UI.h"

#include "Mesh.h"
#include "MeshManager.h"
#include "SceneNode.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"

#include <iostream>
#include <glad.h>

UI::UI(MeshManager* meshManager, SceneNode* root)
{
	triangleCount = 0; circleCount = 0; squareCount = 0;

	m_MeshManager = meshManager;
	m_Root = root;
	m_ActiveNode = m_Root;
	childToBeName = "";

	rootChildCount = 0;
}

void UI::SetSceneNodeScale(float zoom)
{
	m_Root->GetTransform()->SetScale(glm::vec2(zoom, zoom));
}

void UI::SetActiveNode(SceneNode* node)
{
	m_ActiveNode = node;
}

//Gets called every frame
void UI::Draw()
{
	ImGui::Begin("Menu");
	if(ImGui::BeginMenu("Object Creator"))
	{
		//TO DO: Every object should have their own color manipulation. Every object should move on their own.
		if (ImGui::MenuItem("Square"))
		{
			squareCount++;
			std::string name = "Square " + std::to_string(squareCount);
			auto mesh = m_MeshManager->createSquare(0.5f);
			SceneNode* squareNode = new SceneNode();
			squareNode->AddMesh(mesh);
			squareNode->SetName(name);
			m_Root->AddChild(squareNode);
			SetActiveNode(squareNode);
			rootChildCount++;
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
			rootChildCount++;
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
			rootChildCount++;
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
	ImGui::SliderFloat("Rotation", &m_ActiveNode->GetTransform()->getRotation().x, 0, 360);
	
	glm::vec2 position = m_ActiveNode->GetTransform()->getPosition();
	ImGui::SliderFloat2("Translation", &position.x, -1, 1);
	m_ActiveNode->GetTransform()->SetPosition(position);

	glm::vec3 color = m_ActiveNode->GetColorValues();
	ImGui::ColorEdit3("Color", (float*)&color);
	m_ActiveNode->SetColorValues(color);

	ImGui::Separator();
	if (ImGui::Button("Get VboID"))
	{
		VertexTypeList vertices = {
		   -0.35f, -0.35f, 1.0f,
		   0.2f, -0.2f, 1.0f, 
		   -0.35f, 0.35f, 1.0f, 
		   0.35f, 0.35f, 1.0f 
		};
		
		glBindBuffer(GL_ARRAY_BUFFER, m_ActiveNode->GetMesh()->GetVAO()->GetVboID());
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexTypes) * vertices.size(), &vertices[0]);
		//The offset that is 0 rn can be changed to be the same as how we fed the data in VAO Class.
	}
	ImGui::End(); //End of Properties Panel

	//Incomplete Save System
	/*ImGui::Begin("File Management");
	if (ImGui::Button("Save"))
	{
		//m_FileManager.SaveFile(m_Root);
	}
	if (ImGui::Button("Load"))
	{
		//m_FileManager.LoadFile();
	}
	if (ImGui::Button("Delete"))
	{
		//Delete file
	}
	ImGui::End();*/

	ImGui::Begin("Hierarchy"); //Hierarchy panel
		DrawTree(m_Root);
		if (oldChildCount != rootChildCount) {
			oldChildCount = rootChildCount;
			for(auto child : m_Root->GetChildList())
			{
				VertexTypeList vertices;
				vertices.resize(12);
				//std::cout << "X and Y of the Whole Object" << std::endl;
				glBindBuffer(GL_ARRAY_BUFFER, child->GetMesh()->GetVAO()->GetVboID());
				glGetBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexTypes)*vertices.size(), &vertices[0]);
				m_ObjCoordinates.push_back(glm::vec2(child->GetTransform()->getPosition().x, child->GetTransform()->getPosition().y));
				m_VertexList.push_back(vertices);
				m_VboIDList.push_back(child->GetMesh()->GetVAO()->GetVboID());
				//X***std::cout << child->GetTransform()->getMatrix()[2][0] << std::endl;
				//Y***std::cout << child->GetTransform()->getMatrix()[2][1] << std::endl;
				//std::cout << "-----------------------------------" << std::endl;
			}
		}
		/*for (auto vertexElement : m_VertexList)
		{
			for (auto element : vertexElement)
			{
				std::cout << element << std::endl;
			}
		}*/
	ImGui::End();
}
//VertexTypeList vertices = {
//		-0.7 / 2, -0.7 / 2, 1.0f, //left bottom point 0
//		0.4 / 2, -0.4 / 2, 1.0f, // right bottom point 1 
//		-0.7 / 2, 0.7 / 2, 1.0f, //left top point 2 
//		0.7 / 2, 0.7 / 2, 1.0f // right top 3
//};
void UI::DrawTree(SceneNode* node)
{
	if (node)
	{
		unsigned int flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		if (node == m_ActiveNode)
		{
			flags |= ImGuiTreeNodeFlags_Selected;
		}
		if (node->GetChildList().size() == 0) //If node has no child, don't show arrow.
		{
			flags |= ImGuiTreeNodeFlags_Leaf;
		}
		if (ImGui::TreeNodeEx(node->GetName().c_str(), flags))
		{
			if (ImGui::BeginDragDropTarget())//Drop procedures.
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Organise_Tree"))
				{
					node->AddChild((*(SceneNode**)payload->Data));
				}

				ImGui::EndDragDropTarget();
			}
			if (ImGui::IsItemActive())
			{
				m_ActiveNode = node;
				if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) //No flags set bc every node is both source and targets.
				{
					//Set it to carry nodes
					ImGui::SetDragDropPayload("Organise_Tree", &node, sizeof(SceneNode*), ImGuiCond_Once);
					ImGui::EndDragDropSource();
				}
			}
			for (int i = 0; i < node->GetChildCount(); i++)
			{ //Write sceneNode's childs to panel
				DrawTree(node->GetChild(i));
			}
			ImGui::TreePop();
		}
	}
}

std::vector<VertexTypeList> UI::GetVertexList()
{
	return m_VertexList;
}

std::vector<unsigned int> UI::GetVboIDList()
{
	return m_VboIDList;
}

std::vector<glm::vec2> UI::GetObjCoordinates()
{
	return m_ObjCoordinates;
}

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