#pragma once

#include <fstream>
#include <string>
#include <vector>

class SceneNode;

class FileManager
{
public:
	void SaveFile(SceneNode* node);
	void DeleteFile();
	void LoadFile();
	
private:
	std::fstream											file;

	std::vector <std::string> Split(std::string str, char separator);
};