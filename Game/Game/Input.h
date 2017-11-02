#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

//Forward include the same hierachy class Window
class Window;

//Class that holds all the input logic needed in the game
class Input {

#pragma region Singleton
private:
	//Private static instance of class
	static Input* instance;

	//Private constructor to prevent instancing
	Input();

public:
	//Static Get Method
	static Input* GetInstance();
#pragma endregion

public:
	//Destructor
	~Input();

	//Setup input method, sets references
	void SetupInput();

	//Update pollEvent method
	void UpdatePollEvent();

	//Key pressed method, takes a key to check
	bool KeyPressed(sf::Keyboard::Key key);
	//Key down method, takes a key to check
	bool KeyDown(sf::Keyboard::Key key);
	//Key released method, takes a key to check
	bool KeyReleased(sf::Keyboard::Key key);

	//Method to get the mouse position as a vector2
	sf::Vector2i& GetMousePosition();

private:
	//Window Event, when a Event happens it's basicly input
	sf::Event event;

	//Pointer to the RenderWindow class
	Window* renderWindow;
	//Pointer to the window of the RenderWindow class
	sf::RenderWindow* window;

	//Bool to determine if a key is pressed
	bool keyPressed;

	//Local mouse position vector2
	sf::Vector2i mousePosition;
};

