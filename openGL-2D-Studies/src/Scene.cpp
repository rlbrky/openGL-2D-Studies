#include "Scene.h"
#include <glad.h>
#include "MeshManager.h"
#include "VAOManager.h"
#include "SceneNode.h"
#include "WindowTransform.h"
#include "WindowScene.h"
#include "Grid.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

Scene::Scene(GLFWwindow* myWindow)
{
	gridVAO = grid.createGrid(10);
	m_VaoManager = new VAOManager();
	m_MeshManager = new MeshManager(m_VaoManager);
	shader = new Shader();
	BindShader();
	m_Root = new SceneNode();
	m_Root->SetName("Scene");
	m_WindowTransform = new WindowTransform(m_MeshManager, m_Root);
	m_WindowScene = new WindowScene(m_Root);
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

	m_Root->Draw(shader);
	DrawGui();
}

void Scene::Update()
{
	m_Root->Update();
}

void Scene::AddNodeToScene(SceneNode* newNode)
{
	m_Root->AddChild(newNode);
}

//Can add parameters for different shaders.
void Scene::BindShader()
{
	shader->CreateFromFiles(vertexShader, fragmentShader);
}

WindowTransform* Scene::GetWindowTransform() {
	return m_WindowTransform;
}

void Scene::DrawGui()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	//Creating Scene
	m_WindowTransform->Draw();
	m_WindowScene->Draw();
	SceneNode* activeNode = m_WindowScene->GetActiveNode();
	m_WindowTransform->SetActiveNode(activeNode);

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

MeshManager* Scene::getMeshManager()
{
	return m_MeshManager;
}

VAOManager* Scene::GetVaoManager() {
	return m_VaoManager;
}