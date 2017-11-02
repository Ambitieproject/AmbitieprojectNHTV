#include "Input.h"
#include "Window.h"
#include "Game.h"

sf::Event Input::event;
Window* Input::renderWindow;
sf::RenderWindow* Input::window;
bool Input::keyPressed;
sf::Vector2i Input::mousePosition;

//Setup input method, sets references
void Input::SetupInput() {
	//Set RenderWindow references to Game class singleton's RenderWindow class
	renderWindow = Window::GetInstance();
	//Set SFML RenderWindow class
	window = &renderWindow->GetWindow();
	//Set key pressed bool to false
	keyPressed = false;
}

//Update pollEvent method
void Input::UpdatePollEvent() {
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
bool Input::KeyPressed(sf::Keyboard::Key key) {
	//if the key that is pressed is the given key,
	//and the KeyPressed Event of SFML is called,
	//and you didn't press a key yet
	if (event.key.code == key && event.type == sf::Event::KeyPressed && !keyPressed) {
		keyPressed = true;
		return true;
	}
	else {
		return false;
	}
}

//Key down method, takes a key to check
bool Input::KeyDown(sf::Keyboard::Key key) {
	//Using the standard IsKeyPressed method of SFML
	if (sf::Keyboard::isKeyPressed(key)) {
		return true;
	}
}

//Key released method, takes a key to check
bool Input::KeyReleased(sf::Keyboard::Key key) {
	//if the key that is pressed is the given key,
	//and the KeyReleased Event of SFML is called,
	if (event.key.code == key && event.type == sf::Event::KeyReleased) {
		return true;
	}
	else {
		return false;
	}
}

//Method to get the mouse position as a vector2
sf::Vector2i & Input::GetMousePosition() {
	mousePosition = sf::Mouse::getPosition(*window);
	return mousePosition;
}
