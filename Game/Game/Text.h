#pragma once

#include <SFML\Graphics.hpp>

#include "Component.h"
#include "Font.h"

//Namespace Base Component
namespace BC {
	//Text class. Used to display text
	class Text : public sf::Text, public Component {
	public:
		//Constructor
		Text(Font* font);
		//Destructor
		~Text();
	};
}
