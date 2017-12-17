#pragma once

#include <iostream>
#include <string>

class FileReadWrite {
public:
	FileReadWrite();
	~FileReadWrite();

	static void WriteToFile(std::string fileName, std::string category, std::string );
};

