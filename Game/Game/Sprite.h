#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"

//Namespace Base Component
namespace BC {
	//Sprite class
	class Sprite : public sf::Sprite, public Component {
	public:
		//Constructor with values to be added for a Sprite to be created
		Sprite(std::string _pathToSPrite);
		//Destructor
		~Sprite();

		//Override Start method from base Component class
		void Start();
		//Override Update method from base Component class
		void Update(float deltaTime);

		//Gets the texture variable
		sf::Texture& GetTexture();

	private:
		//Texture variable
		sf::Texture texture;
	};
}
