#pragma once
#include <map>
#include <string>
class VertexArrayObject;

class VAOManager
{
public:
	VAOManager();
	void AddNewObject(std::string name, VertexArrayObject* vao);
	VertexArrayObject* GetVAO(std::string name);
private:
	//Hashtable for  VAO's.
	std::map<std::string, VertexArrayObject*> m_VaoMap;
};