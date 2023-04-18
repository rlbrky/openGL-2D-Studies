#include "SceneNode.h"
#include "Shader.h"

SceneNode::SceneNode(SceneNode* parent)
{
	m_parent = parent;
	m_transform = new Transform();
}

void SceneNode::Build(MeshManager* MeshManager)
{
	for (auto nextNode : m_childs)
	{
		nextNode->Build(MeshManager);
	}
}

void SceneNode::Start()
{
}

void SceneNode::Update()
{
	//UPDATE Codes
	m_transform->Update();

	for (auto nextNode : m_childs)
	{
		nextNode->Update();
	}
}

void SceneNode::Draw(Shader* shader)
{
	shader->UseShader();
	shader->SetUniformColor(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

	glm::mat3 mtxTransform = m_transform->getMatrix();
	shader->SetUniformMatrixTransform(mtxTransform);

	for (auto nextMesh : m_meshes)
		nextMesh->Draw();
	for (auto nextNode : m_childs)
	{
		
		nextNode->Draw(shader);
	}
}

void SceneNode::AddChild(SceneNode* child)
{//Set child properties.
	m_childs.push_back(child);
	child->GetTransform()->SetParentTransform(m_transform);

	if (!child->GetParent())
	{
		child->SetParent(this);
	}
	else //Remove child from its previous parent.
	{
		SceneNode* tempParent = child->GetParent();
		child->SetParent(this);
		tempParent->RemoveChild(child);
	}
}

void SceneNode::RemoveChild(SceneNode* child)
{
	if (!m_childs.empty())
	{
		int i = 0;
		for (std::vector<SceneNode*>::iterator iter = m_childs.begin(); iter != m_childs.end(); iter++, i++)
		{
			if (m_childs[i]->GetName() == child->GetName())
			{
				m_childs.erase(iter);
				break;
			}
		}
	}
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

SceneNode* SceneNode::GetChildByName(std::string name)
{
	for (auto child : m_childs)
	{
		if (child->GetName() == name)
		{
			return child;
		}
	}
	return nullptr;
}

SceneNode::SceneNodeList SceneNode::GetChildList()
{
	return m_childs;
}

int SceneNode::GetChildCount()
{
	return m_childs.size();
}

SceneNode* SceneNode::GetParent()
{
	return m_parent;
}
Transform* SceneNode::GetTransform()
{
	return m_transform;
}