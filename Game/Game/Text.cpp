#include "Text.h"

//Use Base Components namespace
using namespace BC;

//Constructor
Text::Text(Font* font) {
	//Set font
	setFont(font->GetFont());
	//Set standard position and string value
	setPosition(0, 0);
	setString("Example Text");
}

//Destructor
Text::~Text() {

}
