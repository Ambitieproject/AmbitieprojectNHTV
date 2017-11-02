#pragma once

#include <iostream>
#include <string>

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

#include "Renderer.h"

//Class that holds the Window field and holds the window draw methods
class Window {

#pragma region Singleton
private:
	//Private static instance of class
	static Window* instance;

	//Private constructor to prevent instancing
	Window();

public:
	//Static Get Method
	static Window* GetInstance();
#pragma endregion

public:
	//Destructor
	~Window();

	//Creates a window with custom values
	void CreateWindow(sf::Vector2u windowSize, std::string windowName);

	//Gets the window size
	sf::Vector2u GetWindowSize();
	//Gets the SFML Renderwindow
	sf::RenderWindow& GetWindow();

	//Gets the Render class
	Renderer& GetRenderer();
	
public:
	//Bool that holds the state of SFML Rendwerwindow being closed or not
	bool IsClosed;

private:
	//SFML Renderwindow 
	sf::RenderWindow window;
	//The window size of the SFML Renderwindow in a SFML Vector2u
	sf::Vector2u windowSize;

	//Icon
	sf::Image icon;
	//Path to Icon
	sf::String pathToIconImage = "../Assets/Art/Icon/Icon.png";

	//Render class that lives within a Window class
	Renderer renderer;
};
