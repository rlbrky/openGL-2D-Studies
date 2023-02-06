#include "WindowTransform.h"

#include "Shader.h"
#include "Mesh.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Scene.h"
#include "MeshManager.h"
#include "Transform.h"

WindowTransform::WindowTransform(Scene* scene)
{
	m_scene = scene;
	shader = new Shader();
	BindShader();
}

//Can add parameters for different shaders.
void WindowTransform::BindShader() {
	shader->CreateFromFiles(vertexShader, fragmentShader);
}

void WindowTransform::setTransform(Transform* transform)
{
	m_Transform = transform;
}

void WindowTransform::Draw()
{
	for (auto& mesh: meshList)
	{
		shader->UseShader();
		shader->SetUniformColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		shader->SetUniformMatrixTransform(m_Transform->getMatrix());
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
		meshList.push_back(*m_scene->getMeshManager()->createCircle(0.5f, 4));
	}
	glm::vec2& angles = m_Transform->getEulerAngles();
	glm::vec2& position = m_Transform->getPosition();
	ImGui::SliderFloat("rotation", &angles.x, 0, 360);
	ImGui::SliderFloat2("transition", &position.x, -1, 1);
	//SLIDERFLOAT--IMGUI -- vec3 olarak deðerleri shadera at.
	ImGui::End();
	ImGui::EndFrame();

	ImGui::Render();

	m_Transform->setPosition(position);
	m_Transform->setEulerAngles(angles);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}