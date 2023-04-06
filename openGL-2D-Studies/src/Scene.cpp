#include "Scene.h"
#include <glad.h>
#include "MeshManager.h"
#include "VAOManager.h"
#include "WindowTransform.h"
#include "Grid.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

Scene::Scene(GLFWwindow* myWindow)
{
	gridVAO = grid.createGrid(10);
	m_VaoManager = new VAOManager();
	m_MeshManager = new MeshManager(m_VaoManager);
	m_WindowTransform = new WindowTransform(this);
	Build(myWindow);
}

void Scene::Build(GLFWwindow* myWindow)
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(myWindow, true);
	ImGui_ImplOpenGL3_Init();

	ImGui::StyleColorsDark();
}

void Scene::Draw()
{
	glBindVertexArray(gridVAO);
	grid.gridShader->UseShader();
	glDrawElements(GL_LINES, grid.GetGridIntexCount(), GL_UNSIGNED_INT, 0);

	m_WindowTransform->Draw();
}

WindowTransform* Scene::GetWindowTransform() {
	return m_WindowTransform;
}

MeshManager* Scene::getMeshManager()
{
	return m_MeshManager;
}

VAOManager* Scene::GetVaoManager() {
	return m_VaoManager;
}