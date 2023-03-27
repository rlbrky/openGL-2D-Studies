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
		shader->SetUniformColor(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
		shader->SetUniformMatrixTransform(m_Transform->getMatrix());
		mesh.Draw();
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Hierarchy");
	ImGui::Text("Hierarchy test text");
	ImGui::End();

	ImGui::Begin("Object Creator");

	/*glm::vec2& squareAngles = m_squareTransform->getEulerAngles();
	glm::vec2& squarePosition = m_squareTransform->getPosition();
	glm::vec2& triangleAngles = m_triangleTransform->getEulerAngles();
	glm::vec2& trianglePosition = m_triangleTransform->getPosition();
	*/

	//TO DO: Every object should have their own color manipulation. Every object should move on their own.
	if (ImGui::Button("Square")) {
		meshList.push_back(*m_scene->getMeshManager()->createSquare());
		/*ImGui::Begin("Heirarchy");
		ImGui::Text("Square");
		ImGui::End();
		Buradaki kod yanlýþ bir uygulama, parent child iliþkisini kurabileceðin
		scene node sýnýfýnýn üzerinden bu isim ekleme iþlemleri halledilmeli.
		*/
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

	ImGui::SliderFloat("Square Rotation", &angles.x, 0, 360);
	ImGui::SliderFloat2("Square Transition", &position.x, -1, 1);

	
	/*
	Bu kodlar fikir vermesi için burada

	ImGui::SliderFloat("Square Rotation", &squareAngles.x, 0, 360);
	ImGui::SliderFloat2("Square Transition", &squarePosition.x, -1, 1);

	m_squareTransform->setPosition(squarePosition);
	m_squareTransform->setEulerAngles(squareAngles);

	ImGui::SliderFloat("Triangle Rotation", &triangleAngles.x, 0, 360);
	ImGui::SliderFloat2("Triangle Transition", &trianglePosition.x, -1, 1);

	m_triangleTransform->setPosition(trianglePosition);
	m_triangleTransform->setEulerAngles(triangleAngles);*/

	//SLIDERFLOAT--IMGUI -- vec3 olarak deðerleri shadera at.
	ImGui::End();
	ImGui::EndFrame();

	ImGui::Render();

	m_Transform->setPosition(position);
	m_Transform->setEulerAngles(angles);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}