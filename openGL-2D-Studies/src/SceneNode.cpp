#include "SceneNode.h"

SceneNode::SceneNode(SceneNode* parent)
{
	m_parent = parent;
}

void SceneNode::Build(MeshManager* MeshManager)
{
}

void SceneNode::Start()
{
}

void SceneNode::Update()
{
	//UPDATE ÝÞLEMLERÝ

	for (auto nextNode : m_childs)
		nextNode->Update();
}

void SceneNode::Draw(Shader* shader)
{
	for (auto nextMesh : m_meshes)
		nextMesh->Draw();
}

void SceneNode::AddChild(SceneNode* child)
{
	m_childs.push_back(child);

	if (!child->GetParent())
		child->SetParent(this);
}
void SceneNode::AddMesh(Mesh* mesh)
{
	m_meshes.push_back(mesh);
}
void SceneNode::SetParent(SceneNode* parent)
{
	m_parent = parent;
}
void SceneNode::SetName(const std::string& name)
{
	m_name = name;
}

std::string SceneNode::GetName()
{
	return m_name;
}
SceneNode* SceneNode::GetChild(int index)
{
	if (index < m_childs.size())
		return m_childs[index];

	return nullptr;
}
SceneNode* SceneNode::GetParent()
{
	return m_parent;
}
Transform* SceneNode::GetTransform()
{
	return m_transform;
}