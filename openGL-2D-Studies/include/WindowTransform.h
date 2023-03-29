#pragma once
#include <glm/vec3.hpp>
#include <vector>

//BUNLARA D�KKAT
class Shader;
class Mesh;
class MeshManager;
class Scene;
class Transform;
class SceneNode;

class WindowTransform
{
public:
	WindowTransform(Scene* scene);
	void Draw();
	void BindShader();
	void setTransform(Transform* transform);
private:
	Scene* m_scene;
	Shader* shader;
	Transform* m_Transform;
	SceneNode* sceneNode;
	const char* vertexShader = "Shaders/vertexShader.vert";
	const char* fragmentShader = "Shaders/fragmentShader.frag";
	glm::vec3* m_Transition;
	//std::vector<Mesh> meshList;
	std::vector<Transform> transformList;
};