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

//File read and writer class
class FileReadWrite {
public:
	//Constructor
	FileReadWrite();
	//Destructor
	~FileReadWrite();
	
	//Write a JSON object to a file
	static void WriteJSONToFile(std::string filePath, json& j);
	//Read a JSON object from a file
	static void GetJSONFromFile(std::string filePath, json& j);
};
