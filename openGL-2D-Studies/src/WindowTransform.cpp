#include "WindowTransform.h"

#include "Shader.h"
#include "Mesh.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Scene.h"
#include "MeshManager.h"

WindowTransform::WindowTransform(Scene* scene)
{
	m_scene = scene;
	shader = new Shader();
	BindShader();
}

void WindowTransform::BindTransition(glm::vec3* transition)
{
	m_Transition = transition;
}

//Can add parameters for different shaders.
void WindowTransform::BindShader() {
	shader->CreateFromFiles(vertexShader, fragmentShader);
}

void WindowTransform::Draw()
{
	for (auto& mesh: meshList)
	{
		shader->UseShader();
		shader->SetUniformPositionSetter(glm::vec3(-0.5f, 0.3f, 0.0f));
		shader->SetUniformColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		mesh.Draw();
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();
	ImGui::Begin("Object Creator");
	
	if (ImGui::Button("Square")) {
		meshList.push_back(*m_scene->getMeshManager()->createSquare());
	}
	if (ImGui::Button("Triangle")) {
		meshList.push_back(*m_scene->getMeshManager()->createTriangle());
	}
	//Çalýþmýyor ?
	if (ImGui::Button("Circle")) {
		meshList.push_back(*m_scene->getMeshManager()->createCircle(5.0f, 32));
	}
	//ImGui::SliderFloat("lol", )
	//SLIDERFLOAT--IMGUI -- vec3 olarak deðerleri shadera at.
	ImGui::End();
	ImGui::EndFrame();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}