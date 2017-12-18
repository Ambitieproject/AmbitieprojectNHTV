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
	
	static void WriteToJSONFile(std::string filePath, std::string content);
	static json* GetJSONFromFile(std::string filePath);

private:
	static std::vector<std::fstream*> files;
};

inline void FileReadWrite::WriteToJSONFile(std::string filePath, std::string content) {

	std::fstream file;
	file.open(filePath, std::ios::in);
	std::getline(file, filePath);

	if (file.good() != true) {
		std::ofstream ofstreamFile(filePath);
		json json;
		json[0]["Level"] = 1;
		json[0]["Translations"][0] = { 
			{ "PositionX", 83 }, { "PositionY", 100 }, {"Rotation", 120}
		};
		json[0]["Translations"][1] = {
			{ "PositionX", 83 },{ "PositionY", 100 },{ "Rotation", 120 }
		};
		json[0]["Translations"][2] = {
			{ "PositionX", 83 },{ "PositionY", 100 },{ "Rotation", 120 }
		};
		json[0]["Translations"][3] = {
			{ "PositionX", 83 },{ "PositionY", 100 },{ "Rotation", 120 }
		};
		json[0]["Translations"][4] = {
			{ "PositionX", 83 },{ "PositionY", 100 },{ "Rotation", 120 }
		};
		json[0]["Translations"][5] = {
			{ "PositionX", 83 },{ "PositionY", 100 },{ "Rotation", 120 }
		};

		json[1]["Level"] = 1;
		json[1]["Translations"][0] = {
			{ "PositionX", 83 },{ "PositionY", 100 },{ "Rotation", 120 }
		};
		json[1]["Translations"][1] = {
			{ "PositionX", 83 },{ "PositionY", 100 },{ "Rotation", 120 }
		};
		json[1]["Translations"][2] = {
			{ "PositionX", 83 },{ "PositionY", 100 },{ "Rotation", 120 }
		};
		json[1]["Translations"][3] = {
			{ "PositionX", 83 },{ "PositionY", 100 },{ "Rotation", 120 }
		};
		json[1]["Translations"][4] = {
			{ "PositionX", 83 },{ "PositionY", 100 },{ "Rotation", 120 }
		};
		json[1]["Translations"][5] = {
			{ "PositionX", 83 },{ "PositionY", 100 },{ "Rotation", 120 }
		};

		ofstreamFile << std::setw(5) << json << std::endl;

		return;
	}
}

inline json* FileReadWrite::GetJSONFromFile(std::string filePath) {
	std::ifstream i(filePath);
	json j;
	i >> j;
	return &j;
}
