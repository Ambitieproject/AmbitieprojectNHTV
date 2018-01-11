#include "Font.h"

//Use Base Components namespace
using namespace BC;

//Constructor
Font::Font(std::string _pathToFont) {
	//Load font from a file path
	font.loadFromFile(_pathToFont);
}

//Destructor
Font::~Font() {

}

//Get Font method
sf::Font& Font::GetFont() {
	return font;
}
