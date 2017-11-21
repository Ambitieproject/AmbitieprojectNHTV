#pragma once

#include <iostream>
#include <SFML\Audio.hpp>

#include "Component.h"

//Namespace Base Component
namespace BC {
	//Music class
	class Music : public sf::Music, public Component {
	public:
		//Constructor
		Music(std::string pathToMusic);
		//Destructor
		~Music();

		//Override Start method from base Component class
		void Start();
		//Override Update method from base Component class
		void Update(float deltaTime);
	};
}