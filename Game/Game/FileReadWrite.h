#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <fstream>
#include <map>

#include "json.hpp"

using json = nlohmann::json;

class FileReadWrite {
public:
	//Constructor
	FileReadWrite();
	//Destructor
	~FileReadWrite();
	
	static void WriteJSONToFile(std::string filePath, json& j);
	static json* GetJSONFromFile(std::string filePath);

private:
	static std::vector<std::fstream*> files;
};

inline void FileReadWrite::WriteJSONToFile(std::string filePath, json& j) {
	std::ofstream ofstreamFile(filePath);
	ofstreamFile << std::setw(5) << j << std::endl;
}

inline json* FileReadWrite::GetJSONFromFile(std::string filePath) {
	std::ifstream i(filePath);
	json j;
	i >> j;
	return &j;
}
