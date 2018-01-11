#pragma once

#include <SFML\Graphics.hpp>

//Forward include upper hierachy class Window
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
	//Draw method that draws a vertex count
	void Draw(const sf::Vertex* vertices, size_t vertexCount, sf::PrimitiveType primitiveType, const sf::RenderStates& states = sf::RenderStates::Default);
	//End draw method
	void EndDraw();

private:
	//Reference to sfml renderwindow of the window class
	sf::RenderWindow* window;
};

