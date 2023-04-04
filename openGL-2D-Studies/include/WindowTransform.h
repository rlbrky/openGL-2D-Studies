#pragma once

#include <glm/vec3.hpp>
#include <vector>

//BUNLARA DÝKKAT
class Shader;
class Mesh;
class MeshManager;
class Scene;
class SceneNode;

class WindowTransform
{
public:
	WindowTransform(Scene* scene);
	void Draw();
	void BindShader();
	void SetSceneNodeScale(float zoom);
private:
	Scene* m_scene;
	Shader* shader;
	SceneNode* sceneNode;
	const char* vertexShader = "Shaders/vertexShader.vert";
	const char* fragmentShader = "Shaders/fragmentShader.frag";
	glm::vec3* m_Transition;
	//std::vector<Mesh> meshList;
	std::vector<Transform*> transformList;
};