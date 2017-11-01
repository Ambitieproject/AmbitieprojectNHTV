#include "Window.h"

//Constructor with values to create a window
Window::Window() {
	//Load Icon
	//icon.loadFromFile(pathToIconImage);
	//Set Icon
	//window.setIcon(32, 32, icon.getPixelsPtr());
}

//Destructor
Window::~Window() {

}

//Creates a window with custom values
void Window::CreateWindow(sf::Vector2u windowSize, std::string windowName) {
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
void Window::BeginDraw() {
	//Clears the window with the color black
	window.clear(sf::Color::Black);
}

//Draw method that draws a SFML Drawable
void Window::Draw(sf::Drawable & drawable) {
	//Draw a drawable to the window
	window.draw(drawable);
}

//End draw method
void Window::EndDraw() {
	//Display to the window
	window.display();
}

//Gets the window size
sf::Vector2u Window::GetWindowSize() {
	return windowSize;
}

//Gets the SFML Renderwindow
sf::RenderWindow& Window::GetWindow() {
	return window;
}
