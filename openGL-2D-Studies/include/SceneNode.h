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

	virtual void Build(MeshManager* MeshManager = 0);
	virtual void Start();
	virtual void Update();
	virtual void Draw(Shader* shader);

	void AddChild(SceneNode* child);
	void AddMesh(Mesh* mesh);
	void SetParent(SceneNode* parent);
	void SetName(const std::string& name);
	void SetTransform(Transform* transform);

	std::string GetName();
	SceneNode* GetChild(int index);
	int GetChildCount();
	SceneNode* GetParent();
	Transform* GetTransform();

protected:
	std::string m_name;
	SceneNodeList m_childs;
	SceneNode* m_parent;
	Transform* m_transform;
	MeshList m_meshes;
};

