#include "WindowScene.h"
#include "SceneNode.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

WindowScene::WindowScene(SceneNode* root)
{
	m_Root = root;
	m_ActiveNode = m_Root;
}

void WindowScene::Draw()
{
	ImGui::Begin("Hierarchy"); //hierarchy panel
		DrawTree(m_Root);
	ImGui::End();
}

SceneNode* WindowScene::GetActiveNode()
{
	return m_ActiveNode;
}

void WindowScene::DrawTree(SceneNode* node)
{
	if (node)
	{
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
			for (int i = 0; i < m_Root->GetChildCount(); i++)
			{ //Write sceneNode's childs to panel
				DrawTree(node->GetChild(i));
			}
			ImGui::TreePop();
		}

		if (ImGui::BeginDragDropSource()) //No flags set bc every node is both source and targets.
		{
			//Set it to carry nodes - BE CAREFUL - Could lead to mistakes.
			ImGui::SetDragDropPayload("Organise_Tree", &node, sizeof(node)); //NEED FIX
			ImGui::EndDragDropSource();
		}
		if (ImGui::BeginDragDropTarget())//Drop procedures.
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Organise_Tree")) //NEED FIX
			{
				m_ActiveNode->AddChild((SceneNode*)payload->Data);
			}
		}
		ImGui::EndDragDropTarget();
	}
}