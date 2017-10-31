#pragma once

#include <iostream>
#include <string>

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

//Class that holds the Window field and holds the window draw methods
class RenderWindow {
public:
	//Constructor
	RenderWindow();
	//Destructor
	~RenderWindow();

	//Creates a window with custom values
	void CreateWindow(sf::Vector2u windowSize, std::string windowName);

	//Begin draw method
	void BeginDraw();
	//Draw method that draws a SFML Drawable
	void Draw(sf::Drawable& drawable);
	//End draw method
	void EndDraw();

	//Gets the window size
	sf::Vector2u GetWindowSize();
	//Gets the SFML Renderwindow
	sf::RenderWindow& GetWindow();
	
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
};

