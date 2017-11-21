#pragma once

#include <iostream>
#include <SFML\Audio.hpp>

#include "Component.h"

//Namespace Base Component
namespace BC {
	//Sound class
	class Sound : public sf::Sound, public Component {
	public:
		//Constructor
		Sound(std::string pathToSound);
		//Destructor
		~Sound();

		//Override Start method from base Component class
		void Start();
		//Override Update method from base Component class
		void Update(float deltaTime);

		//Gets the SoundBuffer by reference
		sf::SoundBuffer& GetSoundBuffer();

	public:
		//Local SoundBuffer variable
		sf::SoundBuffer SoundBuffer;
	};
}


