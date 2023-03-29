#include "WindowTransform.h"

#include "Shader.h"
#include "Mesh.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Scene.h"
#include "MeshManager.h"
#include "Transform.h"
#include "SceneNode.h"

WindowTransform::WindowTransform(Scene* scene)
{
	m_scene = scene;
	shader = new Shader();
	BindShader();
	sceneNode = new SceneNode();
	sceneNode->SetName("Sahne");
}

//Can add parameters for different shaders.
void WindowTransform::BindShader() {
	shader->CreateFromFiles(vertexShader, fragmentShader);
}

void WindowTransform::setTransform(Transform* transform)
{
	m_Transform = transform;
}

//Gets called every frame
void WindowTransform::Draw()
{
	/*for (auto& mesh : meshList)
	{
		//shader->SetUniformMatrixTransform(m_Transform->getMatrix());
		//mesh.Draw();
		sceneNode->SetTransform(m_Transform);
		sceneNode->AddMesh(&mesh);
	}*/

	sceneNode->Draw(shader);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Hierarchy");
	ImGui::Text("Hierarchy test text");
	//TO DO: SceneNode'un çocuklarý arasýnda iterate edip isimlerinin sahne hiyerarþisine yazdýrýlmasý.
	ImGui::Text(sceneNode->GetName().c_str());
	ImGui::End();

	ImGui::Begin("Object Creator");

	/*glm::vec2& squareAngles = m_squareTransform->getEulerAngles();
	glm::vec2& squarePosition = m_squareTransform->getPosition();
	glm::vec2& triangleAngles = m_triangleTransform->getEulerAngles();
	glm::vec2& trianglePosition = m_triangleTransform->getPosition();
	*/

	//TO DO: Every object should have their own color manipulation. Every object should move on their own.
	if (ImGui::Button("Square")) {
		auto& mesh = *m_scene->getMeshManager()->createSquare();
		SceneNode* squareNode = new SceneNode();
		squareNode->SetTransform(m_Transform);
		squareNode->AddMesh(&mesh);
		squareNode->SetName("KARE");
		sceneNode->AddChild(squareNode);

		//Düzgün çalýþmaz.
		ImGui::Begin("Hierarchy");
		ImGui::Text(squareNode->GetName().c_str());
		ImGui::End();
	}
	if (ImGui::Button("Triangle")) {
		auto& mesh = *m_scene->getMeshManager()->createTriangle();
		SceneNode* triangleNode = new SceneNode();
		triangleNode->SetTransform(m_Transform);
		triangleNode->AddMesh(&mesh);
		triangleNode->SetName("ÜÇGEN");
		sceneNode->AddChild(triangleNode);

		//Düzgün çalýþmaz. Anlýk çalýþýp sonra siliyor, ADD metodu eklenmesi gerekebilir.
		ImGui::Begin("Hierarchy");
		ImGui::Text(triangleNode->GetName().c_str());
		ImGui::End();
	}
	//Çalýþmýyor ?
	if (ImGui::Button("Circle")) {
		//meshList.push_back(*m_scene->getMeshManager()->createCircle(0.5f, 4));
		auto& mesh = *m_scene->getMeshManager()->createCircle(0.5f, 12);
		sceneNode->SetTransform(m_Transform);
		sceneNode->AddMesh(&mesh);
	}

	glm::vec2& angles = m_Transform->getEulerAngles();
	glm::vec2& position = m_Transform->getPosition();

	//BU kýsým doðrudan sahneyi etkiliyor, objelerin tek tek manipülasyonu için ayrý bir yöntem gerek.
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