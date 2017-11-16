#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"

//Namespace Base Component
namespace BC {
	//Sprite class
	class Sprite : public Component {
	public:
		//Constructor with values to be added for a Sprite to be created
		Sprite(std::string _pathToSPrite, bool _isStatic);
		//Destructor
		~Sprite();

		//Override Start method from base Component class
		void Start();
		//Override Update method from base Component class
		void Update(float deltaTime);

		//SetFillScale Method that fills the scale of the sprite
		void SetFillScale(int x, int y);
		//Set position of sprite method
		void SetPosition(float x, float y);
		//Set scale of sprite
		void SsetScale(float x, float y);

		//Gets the sprite variable
		sf::Sprite& GetSprite();
		//Gets the texture variable
		sf::Texture& GetTexture();

	private:
		//Sprite variable
		sf::Sprite sprite;
		//Texture variable
		sf::Texture texture;
	};
}
