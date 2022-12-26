#pragma once
#include <glm/vec3.hpp>
#include <vector>

//BUNLARA DÝKKAT
class Shader;
class Mesh;
class MeshManager;
class Scene;

class WindowTransform
{
public:
	WindowTransform(Scene* scene);
	void Draw();
	void BindShader();
	void BindTransition(glm::vec3* transition);
private:
	Scene* m_scene;
	Shader* shader;
	const char* vertexShader = "Shaders/vertexShader.vert";
	const char* fragmentShader = "Shaders/fragmentShader.frag";
	glm::vec3* m_Transition;
	std::vector<Mesh> meshList;
};