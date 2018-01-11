#pragma once

#include <SFML\Graphics.hpp>

//Include needed header files
#include "Component.h"

//Namespace Base Component
namespace BC {
	//Font class. Font is needed for a text
	class Font : public Component {
	public:
		//Constructor
		Font(std::string _pathToFont);
		//Destructor
		~Font();

		//Get Font method
		sf::Font& GetFont();
	private:
		//Font
		sf::Font font;
	};
}
