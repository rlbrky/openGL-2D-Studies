#pragma once
#include <map>
#include <string>
class VertexArrayObject;

class VAOManager
{
public:
	VAOManager();
	void AddNewObject(std::string name, VertexArrayObject* vao);				//Add Vertex Array Object to VaoMAP
	VertexArrayObject* GetVAO(std::string name);												//Get Vertex Array Object
private:
	//Hashtable for  VAO's.
	std::map<std::string, VertexArrayObject*> m_VaoMap;
};