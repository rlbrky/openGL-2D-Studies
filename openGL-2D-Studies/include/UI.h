#pragma once

#include "FileManager.h"
#include <glm/vec3.hpp>
#include <vector>
#include <string>

class Mesh;
class MeshManager;
class SceneNode;

class UI
{
public:
	UI(MeshManager* meshManager, SceneNode* root);

	void Draw();																																//Create Object Creator and Properties Panels.

	void SetSceneNodeScale(float zoom);
	void SetActiveNode(SceneNode* node);

	void DrawTree(SceneNode* node);																					//Create hierarchy panel using TreeNodeEX from imgui

private:
	MeshManager*				m_MeshManager;
	SceneNode*						m_Root;
	SceneNode*						m_ActiveNode;
	FileManager					m_FileManager;
	
	int										triangleCount, circleCount, squareCount;
	std::string							childToBeName;
};