#pragma once

class SceneNode;

class WindowScene
{
private:
	SceneNode*		m_Root;
	SceneNode*		m_ActiveNode;
public:
	WindowScene(SceneNode* root);
	SceneNode* GetActiveNode();
	void Draw();
	void DrawTree(SceneNode* node);
};