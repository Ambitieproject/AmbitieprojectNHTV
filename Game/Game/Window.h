#pragma once

#include <iostream>
#include <string>

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

#include "Renderer.h"

//Class that holds the Window field and holds the window draw methods
class Window {
public:
	//Constructor
	Window();
	//Destructor
	~Window();

	//Creates a window with custom values
	static void CreateWindow(sf::Vector2u size, std::string name, std::string iconPath);

	//Sets a plain color as the background of the window
	static void SetWindowRenderColor(sf::Color color);

	//Gets the window size
	static sf::Vector2u GetWindowSize();
	//Gets the SFML Renderwindow
	static sf::RenderWindow& GetWindow();

	//Gets the Render class
	static Renderer& GetRenderer();
	
public:
	//Bool that holds the state of SFML Rendwerwindow being closed or not
	static bool IsClosed;

private:
	//SFML Renderwindow 
	static sf::RenderWindow window;
	//The window size of the SFML Renderwindow in a SFML Vector2u
	static sf::Vector2u windowSize;

	//Icon
	static sf::Image icon;

	//Render class that lives within a Window class
	static Renderer renderer;
};
