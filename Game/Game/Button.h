#pragma once

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"

//Include needed header files
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

		//Handles variable setting when the button is clicked
		void HandleClicking();

		//Returns the click state of the button
		bool IsClicked();

		//Gets the current button sprite
		sf::Sprite& GetCurrentButtonSprite();

	private:
		//Is clicked value
		bool isClicked;

		//Normal button texture
		sf::Texture normalTexture;
		//Hovered button texture
		sf::Texture hoveredTexture;
		//Pressed button texture
		sf::Texture pressedTexture;

		//The sprite for the button
		sf::Sprite currentButtonSpriteImage;

		//Bool that sets to true when button is clicked
		bool activateButtonUp;
		//Timer that handles the time a function can be called when a button is clicked, should be 1 time
		float deActiveButtonTimer;
	};
}


