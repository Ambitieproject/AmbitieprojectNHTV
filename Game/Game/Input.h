#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

//Forward include the same hierachy class Window
class Window;

//Class that holds all the input logic needed in the game
class Input {

public:
	//Setup input method, sets references
	static void SetupInput();

	//Update pollEvent method
	static void UpdatePollEvent();

	//Key pressed method, takes a key to check
	static bool KeyPressed(sf::Keyboard::Key key);
	//Key down method, takes a key to check
	static bool KeyDown(sf::Keyboard::Key key);
	//Key released method, takes a key to check
	static bool KeyReleased(sf::Keyboard::Key key);

	//Method to get the mouse position as a vector2
	static sf::Vector2i& GetMousePosition();

private:
	//Window Event, when a Event happens it's basicly input
	static sf::Event event;

	//Pointer to the RenderWindow class
	static Window* renderWindow;
	//Pointer to the window of the RenderWindow class
	static sf::RenderWindow* window;

	//Bool to determine if a key is pressed
	static bool keyPressed;

	//Local mouse position vector2
	static sf::Vector2i mousePosition;
};

