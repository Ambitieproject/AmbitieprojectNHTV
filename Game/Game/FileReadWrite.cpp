#include "FileReadWrite.h"

//Constructor
FileReadWrite::FileReadWrite() {

}

//Destructor
FileReadWrite::~FileReadWrite() {

}

//Write a JSON object to a file
void FileReadWrite::WriteJSONToFile(std::string filePath, json& j) {
	//Create ofstream
	std::ofstream ofstream(filePath);
	//Load offstream from JSON object into ofstream object
	ofstream << std::setw(5) << j << std::endl;
}

//Read a JSON object from a file
void FileReadWrite::GetJSONFromFile(std::string filePath, json& j) {
	//Create ifstream
	std::ifstream ifstream(filePath);
	//Get data from iffstream object into JSON object
	ifstream >> j;
}
