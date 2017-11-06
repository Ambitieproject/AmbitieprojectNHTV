#pragma once

#include <SFML\Graphics.hpp>

class Window;

class Renderer {
public:
	//Constructor
	Renderer();
	//Destructor
	~Renderer();

	//Sets the renderer up, does reference setup
	void SetupRenderer();

	//Begin draw method
	void BeginDraw();
	//Draw method that draws a SFML Drawable
	void Draw(sf::Drawable& drawable);
	//End draw method
	void EndDraw();

private:
	//Reference to sfml renderwindow of the window class
	sf::RenderWindow* window;

	//Reference to the scene that needs to be rendered
};

