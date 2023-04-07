#pragma once

#include <glm/vec3.hpp>
#include <vector>

class Mesh;
class MeshManager;
class SceneNode;

class WindowTransform
{
public:
	WindowTransform(MeshManager* meshManager, SceneNode* root);
	void Draw();
	void SetSceneNodeScale(float zoom);
	void SetActiveNode(SceneNode* node);
private:
	MeshManager*				m_MeshManager;
	SceneNode*						m_Root;
	SceneNode*						m_ActiveNode;
	//glm::vec3* m_Transition;
};