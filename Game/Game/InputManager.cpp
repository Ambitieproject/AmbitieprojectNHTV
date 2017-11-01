#include "InputManager.h"
#include "Window.h"
#include "Game.h"

//Constructor
InputManager::InputManager() {
	
}

//Destructor
InputManager::~InputManager() {

}

//Setup input method, sets references
void InputManager::SetupInput() {
	//Set RenderWindow references to Game class singleton's RenderWindow class
	renderWindow = &Game::GetInstance()->GetWindowClass();
	//Set SFML RenderWindow class
	window = &renderWindow->GetWindow();
	//Set key pressed bool to false
	keyPressed = false;
}

//Update pollEvent method
void InputManager::UpdatePollEvent() {
	//Make seperate Event just to check basic events
	sf::Event _event;

	//PollEvent the sperate Event
	if (window->pollEvent(_event)) {
		//Close window if exit button is pressed
		if (_event.type == sf::Event::Closed) {
			renderWindow->IsClosed = true;
		}
		//Set keypressed bool to false if a key is released
		else if (_event.type == sf::Event::KeyReleased) {
			keyPressed = false;
		}
	}

	//Set global Event to the custom Event
	event = _event;
}

//Key pressed method, takes a key to check
bool InputManager::KeyPressed(sf::Keyboard::Key _key) {
	//if the key that is pressed is the given key,
	//and the KeyPressed Event of SFML is called,
	//and you didn't press a key yet
	if (event.key.code == _key && event.type == sf::Event::KeyPressed && !keyPressed) {
		keyPressed = true;
		return true;
	}
	else {
		return false;
	}
}

//Key down method, takes a key to check
bool InputManager::KeyDown(sf::Keyboard::Key _key) {
	//Using the standard IsKeyPressed method of SFML
	if (sf::Keyboard::isKeyPressed(_key)) {
		return true;
	}
}

//Key released method, takes a key to check
bool InputManager::KeyReleased(sf::Keyboard::Key _key) {
	//if the key that is pressed is the given key,
	//and the KeyReleased Event of SFML is called,
	if (event.key.code == _key && event.type == sf::Event::KeyReleased) {
		return true;
	}
	else {
		return false;
	}
}

//Method to get the mouse position as a vector2
sf::Vector2i & InputManager::GetMousePosition() {
	mousePosition = sf::Mouse::getPosition(*window);
	return mousePosition;
}
