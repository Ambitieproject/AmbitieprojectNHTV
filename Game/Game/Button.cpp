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
	std::cout << pressedImagePath << std::endl;
	currentButtonSpriteImage = new Sprite(normalImagePath);
	isClicked = false;
}

//Destructor
Button::~Button() {
	delete currentButtonSpriteImage;
}

void Button::Start() {
	Component::Start();
}

void Button::Update(float deltaTime) {
	Component::Update(deltaTime);

	const sf::Vector2f mousePos = sf::Vector2f(Input::GetMousePosition().x, Input::GetMousePosition().y);

	if (currentButtonSpriteImage->getLocalBounds().contains(mousePos)) {
		if (Input::GetMouseKeyDown(sf::Mouse::Button::Left)) {
			currentButtonSpriteImage->setTexture(pressedTexture);
		}
		else {
			currentButtonSpriteImage->setTexture(hoveredTexture);
		}
		
	}
	else {
		currentButtonSpriteImage->setTexture(normalTexture);
	}
}

bool BC::Button::OnClicked() {
	return isClicked;
}

Sprite& Button::GetCurrentButtonSprite() {
	return *currentButtonSpriteImage;
}
