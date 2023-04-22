#pragma once
#include <vector>
#include <string>
#include "Transform.h"
#include "Mesh.h"

class Shader;

class SceneNode
{
public:
	typedef std::vector<SceneNode*> SceneNodeList;

	SceneNode(SceneNode* parent = nullptr);

	virtual void Build(MeshManager* MeshManager = 0);		//Call build func for every node.
	virtual void Start();																			//Empty for now.
	virtual void Update();																		//Update transform for every node.
	virtual void Draw(Shader* shader);											//Send transform matrix to shaders, set child scales etc.

	void AddChild(SceneNode* child);												//Sets child parent automatically.
	void AddMesh(Mesh* mesh);
	void SetParent(SceneNode* parent);
	void SetName(const std::string& name);
	void SetTransform(Transform* transform);
	void SetColorValues(glm::vec3 colorVec);

	std::string GetName();
	glm::vec3 GetColorValues();

	SceneNode* GetChild(int index);
	SceneNode* GetChildByName(std::string name);
	int GetChildCount();
	SceneNodeList GetChildList();
	void RemoveChild(SceneNode* child);

	SceneNode* GetParent();
	Transform* GetTransform();

protected:
	std::string					m_name;
	SceneNodeList		m_childs;
	SceneNode*				m_parent;
	Transform*				m_transform;
	MeshList					m_meshes;
	glm::vec3					m_color;
};

