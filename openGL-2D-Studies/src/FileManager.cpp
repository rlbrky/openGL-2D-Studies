#include "FileManager.h"
#include "SceneNode.h"

#include <iostream>

void FileManager::SaveFile(SceneNode* node)
{
	//Pick position, rotation, scale, color info and other necessary stuff and write them to file.
	file.open("savefile.txt", std::ios::app);
	if (file.is_open())
	{
		file << "ALO / Test / BOMBA";
		file.close();
	}
	else std::cout << "Unable open file" << std::endl;
}

void FileManager::DeleteFile()
{
	
}

void FileManager::LoadFile() //Pick the saved things from file.
{
	std::string line;
	char separator = '/';
	std::vector<std::string> content;

	file.open("savefile.txt", std::ios::in);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			content = Split(line, separator);
		}
		file.close();
	}
	else std::cout << "Unable to open file";

	for (auto iter : content) //Main loading stuff.
	{
		std::cout << iter << std::endl;
	}
}

std::vector<std::string> FileManager::Split(std::string str, char separator) 
{
	std::vector <std::string> content;
	int startIndex = 0, endIndex = 0;
	for (int i = 0; i <= str.size(); i++)
	{
		// If we reached the end of the word or the end of the input.
		if (str[i] == separator || i == str.size()) 
		{
			endIndex = i;
			std::string temp;
			temp.append(str, startIndex, endIndex - startIndex);
			content.push_back(temp);
			startIndex = endIndex + 1;
		}
	}
	return content;
}