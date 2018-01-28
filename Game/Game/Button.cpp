#include "Button.h"

//Use Base Components namespace
using namespace BC;

//Constructor
Button::Button(std::string normalImagePath, std::string hoveredImagePath, std::string pressedImagePath) {
	//Set textures depending on the file paths being empty
	if (normalImagePath != "") {
		normalTexture.loadFromFile(normalImagePath);
	}
	if (hoveredImagePath != "") {
		hoveredTexture.loadFromFile(hoveredImagePath);
	}
	if (pressedImagePath != "") {
		pressedTexture.loadFromFile(pressedImagePath);
	}

	//Set a standard texture to start the button with
	currentButtonSpriteImage.setTexture(normalTexture);
	
	//Set default values
	isClicked = false;
	isHoldingDown = false;
	deActiveButtonTimer = 0;
}

//Destructor
Button::~Button() {

}

//Override Start method from base Component class
void Button::Start() {
	Component::Start();
}

//Override Update method from base Component class
void Button::Update(float deltaTime) {
	Component::Update(deltaTime);

	//Get the mouse position
	const sf::Vector2f mousePos = sf::Vector2f(Input::GetMousePosition().x, Input::GetMousePosition().y);

	//If countdown for clicking button is reached
	if (deActiveButtonTimer > 0.3f) {
		//If mouse is inside the button sprite
		if (currentButtonSpriteImage.getGlobalBounds().contains(mousePos)) {

			//Set hover texture
			if (hoveredTexture.getSize() != sf::Vector2u(0, 0)) {
				currentButtonSpriteImage.setTexture(hoveredTexture);
			}

			//If left mouse is clicked
			if (Input::GetMouseKeyDown(sf::Mouse::Button::Left)) {
				isHoldingDown = true;
				if (pressedTexture.getSize() != sf::Vector2u(0, 0)) {
					currentButtonSpriteImage.setTexture(pressedTexture);
				}

			}
			else {
				//If button was held down earlier
				if (isHoldingDown) {
					//If left mouse is released
					if (Input::GetMouseKeyUp(sf::Mouse::Button::Left)) {
						isClicked = true;
						//If texture is buttonPressed so it is actually being pressed
						if (currentButtonSpriteImage.getTexture() == &pressedTexture) {
							currentButtonSpriteImage.setTexture(hoveredTexture);
						}
					}
				}
				
			}
		}
		//If mouse is not inside the button sprite
		else {
			//If Mouse is not down set texture
			if (!Input::GetMouseKeyDown(sf::Mouse::Button::Left)) {
				if (normalTexture.getSize() != sf::Vector2u(0, 0)) {
					currentButtonSpriteImage.setTexture(normalTexture);
				}
			}
		}
	}
	else {
		//Increase button timer
		deActiveButtonTimer = deActiveButtonTimer + deltaTime;
	}	
}

//Handles variable setting when the button is clicked
void Button::HandleClicking() {
	isClicked = true;
	activateButtonUp = true;
}

//Returns the click state of the button
bool Button::IsClicked() {
	if (isClicked) {
		//Reset variables
		isClicked = false;
		deActiveButtonTimer = 0;
		return true;
	}
	else {
		return false;
	}
}

//Gets the current button sprite
sf::Sprite& Button::GetCurrentButtonSprite() {
	return currentButtonSpriteImage;
}
