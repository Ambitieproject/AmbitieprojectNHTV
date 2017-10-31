#include "RenderWindow.h"

//Constructor with values to create a window
RenderWindow::RenderWindow() {
	//Load Icon
	//icon.loadFromFile(pathToIconImage);
	//Set Icon
	//window.setIcon(32, 32, icon.getPixelsPtr());
}

//Destructor
RenderWindow::~RenderWindow() {

}

//Creates a window with custom values
void RenderWindow::CreateWindow(sf::Vector2u windowSize, std::string windowName) {
	//Creates window with assigned values
	window.create(sf::VideoMode(windowSize.x, windowSize.y), windowName, sf::Style::Close);
	//Gets window size values
	this->windowSize = window.getSize();
	//Set isClosed to false
	IsClosed = false;
	//Set framerate
	window.setFramerateLimit(60);
}

//Begin draw method
void RenderWindow::BeginDraw() {
	//Clears the window with the color black
	window.clear(sf::Color::Black);
}

//Draw method that draws a SFML Drawable
void RenderWindow::Draw(sf::Drawable & drawable) {
	//Draw a drawable to the window
	window.draw(drawable);
}

//End draw method
void RenderWindow::EndDraw() {
	//Display to the window
	window.display();
}

//Gets the window size
sf::Vector2u RenderWindow::GetWindowSize() {
	return windowSize;
}

//Gets the SFML Renderwindow
sf::RenderWindow& RenderWindow::GetWindow() {
	return window;
}
