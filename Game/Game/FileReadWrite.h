#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

//Include and use for making use of the Modern JSON library frmo nlohmann
//For more information go to the json hpp file 
#include "json.hpp"
using json = nlohmann::json;

class FileReadWrite {
public:
	//Constructor
	FileReadWrite();
	//Destructor
	~FileReadWrite();
	
	static void WriteJSONToFile(std::string filePath, json& j);
	static void GetJSONFromFile(std::string filePath, json& j);

private:
	static std::vector<std::fstream*> files;
};

inline void FileReadWrite::WriteJSONToFile(std::string filePath, json& j) {
	std::ofstream ofstreamFile(filePath);
	ofstreamFile << std::setw(5) << j << std::endl;
}

inline void FileReadWrite::GetJSONFromFile(std::string filePath, json& j) {
	std::ifstream i(filePath);
	i >> j;
}
