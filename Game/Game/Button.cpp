#include "Button.h"

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
	//Set isClicked to false by default
	isClicked = false;

	deActiveButtonTimer = 0;
}

//Destructor
Button::~Button() {

}

void Button::Start() {
	Component::Start();
}

void Button::Update(float deltaTime) {
	Component::Update(deltaTime);

	//Get the mouse position
	const sf::Vector2f mousePos = sf::Vector2f(Input::GetMousePosition().x, Input::GetMousePosition().y);

	//If mouse is inside the button sprite
	if (currentButtonSpriteImage.getGlobalBounds().contains(mousePos)) {
		//If left mouse is clicked
		if (Input::GetMouseKeyDown(sf::Mouse::Button::Left)) {
			currentButtonSpriteImage.setTexture(pressedTexture);
		}
		else {
			//If left mouse is released
			if (Input::GetMouseKeyUp(sf::Mouse::Button::Left)) {
				//If texture is buttonPressed so it is actually being pressed
				if (currentButtonSpriteImage.getTexture() == &pressedTexture) {
					HandleClicking();
					currentButtonSpriteImage.setTexture(hoveredTexture);
				}
			}
			else {
				currentButtonSpriteImage.setTexture(hoveredTexture);
			}

		}

	}
	//If mouse is not inside the button sprite
	else {
		//If Mouse is not down set texture
		if (!Input::GetMouseKeyDown(sf::Mouse::Button::Left)) {
			currentButtonSpriteImage.setTexture(normalTexture);
		}
	}

	//If activateButtonUp is true
	if (activateButtonUp) {
		//Increase timer with deltaTime
		deActiveButtonTimer += deltaTime;

		//If timer is bigger then deltaTime which should be one time
		if (deActiveButtonTimer > deltaTime) {
			//Reset variable
			deActiveButtonTimer = 0;
			activateButtonUp = false;
			isClicked = false;
		}
	}
}

//Handles variable setting when the button is clicked
void Button::HandleClicking() {
	isClicked = true;
	activateButtonUp = true;
}

//Returns the click state of the button
bool Button::IsClicked() {
	return isClicked;
}

//Gets the current button sprite
sf::Sprite& Button::GetCurrentButtonSprite() {
	return currentButtonSpriteImage;
}
