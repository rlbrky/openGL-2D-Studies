#include "SceneNode.h"

SceneNode::SceneNode(SceneNode* parent)
{
	m_parent = parent;
	m_transform = new Transform();
}

void SceneNode::Build(MeshManager* MeshManager)
{
}

void SceneNode::Start()
{
}

void SceneNode::Update()
{
	//UPDATE Codes
	m_transform->Update();

	for (auto nextNode : m_childs)
		nextNode->Update();
}

void SceneNode::Draw(Shader* shader)
{
	for (auto nextMesh : m_meshes)
		nextMesh->Draw();
	/*for (auto nextNode : m_childs)
		nextNode->Draw(shader);
		�ocuklar�n �izdirilmesi i�in.
		*/
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

void SceneNode::SetTransform(Transform* transform)
{
	if (m_transform)
		delete m_transform;
	m_transform = transform;
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