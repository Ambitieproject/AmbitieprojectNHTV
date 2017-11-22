#pragma once

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"

#include "Sprite.h"

//Namespace Base Component
namespace BC {
	//Button class
	class Button : public Component {
	public:
		//Constructor
		Button(std::string normalImagePath, std::string hoveredImagePath = "", std::string pressedImagePath = "");
		//Destructor
		~Button();

		//Override Start method from base Component class
		void Start();
		//Override Update method from base Component class
		void Update(float deltaTime);

		bool OnClicked();

		Sprite& GetCurrentButtonSprite();

	private:
		sf::Texture normalTexture;
		sf::Texture hoveredTexture;
		sf::Texture pressedTexture;

		Sprite* currentButtonSpriteImage;

		bool isClicked;
	};
}


