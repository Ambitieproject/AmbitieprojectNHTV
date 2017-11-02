#include "Window.h"

Window* Window::instance = 0;

//Constructor with values to create a window
Window::Window() {
	//Load Icon
	//icon.loadFromFile(pathToIconImage);
	//Set Icon
	//window.setIcon(32, 32, icon.getPixelsPtr());
}

//Static Get Method
Window* Window::GetInstance() {
	if (instance == 0) {
		instance = new Window();
	}

	return instance;
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

	renderer.SetupRenderer();
}

//Gets the window size
sf::Vector2u Window::GetWindowSize() {
	return windowSize;
}

//Gets the SFML Renderwindow
sf::RenderWindow& Window::GetWindow() {
	return window;
}

Renderer & Window::GetRenderer() {
	return renderer;
}
