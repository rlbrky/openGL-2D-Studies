#include "VAOManager.h"
#include "VertexArrayObject.h"

VAOManager::VAOManager()
{

}

void VAOManager::AddNewObject(std::string name, VertexArrayObject* vao) {
	if (!m_VaoMap.count(name))
	{
		m_VaoMap[name] = vao;
	}
}

VertexArrayObject* VAOManager::GetVAO(std::string name) {
	if (m_VaoMap.count(name))
	{
		return m_VaoMap[name];
	}
	return nullptr;
}