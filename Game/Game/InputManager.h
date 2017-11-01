#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

//Forward include the same hierachy class RenderWindow
class RenderWindow;

//Class that holds all the input logic needed in the game
class InputManager {
public:
	//Constructor
	InputManager();
	//Destructor
	~InputManager();

	//Setup input method, sets references
	void SetupInput();

	//Update pollEvent method
	void UpdatePollEvent();

	//Key pressed method, takes a key to check
	bool KeyPressed(sf::Keyboard::Key _key);
	//Key down method, takes a key to check
	bool KeyDown(sf::Keyboard::Key _key);
	//Key released method, takes a key to check
	bool KeyReleased(sf::Keyboard::Key _key);

	//Method to get the mouse position as a vector2
	sf::Vector2i& GetMousePosition();

private:
	//Window Event, when a Event happens it's basicly input
	sf::Event event;

	//Pointer to the RenderWindow class
	RenderWindow* renderWindow;
	//Pointer to the window of the RenderWindow class
	sf::RenderWindow* window;

	//Bool to determine if a key is pressed
	bool keyPressed;

	//Local mouse position vector2
	sf::Vector2i mousePosition;
};

