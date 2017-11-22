#include "Button.h"

using namespace BC;

//Constructor
Button::Button(std::string normalImagePath, std::string hoveredImagePath, std::string pressedImagePath) {
	if (normalImagePath != "") {
		normalTexture.loadFromFile(normalImagePath);
	}
	if (hoveredImagePath != "") {
		hoveredTexture.loadFromFile(hoveredImagePath);
	}
	if (pressedImagePath != "") {
		pressedTexture.loadFromFile(pressedImagePath);
	}

	currentButtonSpriteImage.setTexture(normalTexture);
	isClicked = false;
}

//Destructor
Button::~Button() {

}

void Button::Start() {
	Component::Start();
}

void Button::Update(float deltaTime) {
	Component::Update(deltaTime);

	const sf::Vector2f mousePos = sf::Vector2f(Input::GetMousePosition().x, Input::GetMousePosition().y);

	if (currentButtonSpriteImage.getGlobalBounds().contains(mousePos)) {
		if (Input::GetMouseKeyDown(sf::Mouse::Button::Left)) {
			currentButtonSpriteImage.setTexture(pressedTexture);
		}
		else {
			currentButtonSpriteImage.setTexture(hoveredTexture);
		}
		
	}
	else {
		if (!Input::GetMouseKeyDown(sf::Mouse::Button::Left)) {
			currentButtonSpriteImage.setTexture(normalTexture);
		}
	}

	if (Input::GetMouseKeyUp(sf::Mouse::Button::Left)) {
		if (currentButtonSpriteImage.getTexture() == &pressedTexture) {
			isClicked = true;
			OnClicked();
			currentButtonSpriteImage.setTexture(normalTexture);
		}
	}
}

bool Button::OnClicked() {
	return isClicked;
	std::cout << "is clicked" << std::endl;
}

sf::Sprite& Button::GetCurrentButtonSprite() {
	return currentButtonSpriteImage;
}
