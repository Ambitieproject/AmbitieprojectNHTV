#pragma once

#include <iostream>
#include <map>
#include <SFML\Graphics.hpp>

//Axis struct
struct Axis {
public:
	//Axis name
	std::string AxisName;
	//Positive key of the Axis
	sf::Keyboard::Key PositiveKey;
	//Negative key of the Axis
	sf::Keyboard::Key NegativeKey;

private:
	//Value of the Axis that is calculated depending on the negative and positive key presses
	float value = 0.0f;
	//Axis multiplier, multiplies when a positive or negative key is held down. Increase with axisMultiplier
	float axisMultiplier;
	
	//Friend class Input which needs acces to private members
	friend class Input;
};

//Enum that holds key change choice info
enum ChangeKey {
	PositiveOnly,
	NegativeOnly,
	Both
};

//Forward include the same hierachy class Window
class Window;

//Class that holds all the input logic needed in the game
class Input {
public:
	//Key pressed method, returns the key pressed state
	static bool GetKeyPressed(sf::Keyboard::Key key);
	//Key down method, returns the key down state
	static bool GetKeyDown(sf::Keyboard::Key key);
	//Key released method, returns the key released state
	static bool GetKeyReleased(sf::Keyboard::Key key);

	//Any key pressed method, checks for any input from keyboard
	static bool GetAnyKeyPressed();
	//Any key down method, checks for any input from keyboard
	static bool GetAnyKeyDown();
	//Any key released method, checks for any input from keyboard
	static bool GetAnyKeyReleased();

	//Mouse button pressed method, returns the mouse button pressed state
	static bool GetMouseKeyPressed(sf::Mouse::Button mouseButton);
	//Mouse button down method, returns the mouse button down state
	static bool GetMouseKeyDown(sf::Mouse::Button mouseButton);
	//Mouse button released method, return the mouse button released state
	static bool GetMouseKeyUp(sf::Mouse::Button mouseButton);
	
	//Method to get the mouse position as a vector2
	static sf::Vector2i& GetMousePosition();

	//Creates an Axis with a positive and negative key that can specified
	static void CreateAxis(std::string axisName, sf::Keyboard::Key positiveKey, sf::Keyboard::Key negativeKey);
	//Changes the positive and/or the negative key of an Axis
	static void ChangeAxis(std::string axisName, ChangeKey changeKey, sf::Keyboard::Key newPositiveKey, sf::Keyboard::Key newNegativeKey);
	//Gets the value of an Axis as a float
	static float GetAxis(std::string axisName);
	//Gets the value of an Axis as a raw int
	static int GetAxisRaw(std::string axisName);

private:
	//Setup Input, sets references
	static void SetupInput();

	//Update pollEvent method
	static void UpdatePollEvent(float deltaTime);

private:
	//Window Event, when a Event happens it's basicly input
	static sf::Event event;

	//Pointer to the RenderWindow class
	static Window* renderWindow;
	//Pointer to the window of the RenderWindow class
	static sf::RenderWindow* window;

	//Bool to determine if a key is pressed
	static bool keyPressed;
	//Bool to determine if a mouse button is pressed
	static bool mouseButtonPressed;

	//Local mouse position vector2
	static sf::Vector2i mousePosition;

	//Map that holds the Axis made
	static std::map<std::string, Axis> InputAxis;

	//Copy of the DeltaTime value in the main Game class
	static float deltaTime;

	//Define the friend class Game
	friend class Game;
};
