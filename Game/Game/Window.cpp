#include "Window.h"

//Bool that holds the state of SFML Rendwerwindow being closed or not
bool Window::IsClosed;
//SFML Renderwindow 
sf::RenderWindow Window::window;
//The window size of the SFML Renderwindow in a SFML Vector2u
sf::Vector2u Window::windowSize;
//Render class that lives within a Window class
Renderer Window::renderer;
//Icon
sf::Image Window::icon;

//Constructor with values to create a window
Window::Window() {
	
}

//Destructor
Window::~Window() {

}

//Creates a window with custom values
void Window::CreateWindow(sf::Vector2u size, std::string name, std::string iconPath) {
	//Creates window with assigned values
	window.create(sf::VideoMode(size.x, size.y), name, sf::Style::Close);
	//Gets window size values
	windowSize = window.getSize();
	//Set isClosed to false
	IsClosed = false;
	//Set framerate
	window.setFramerateLimit(60);
	//Setting up the renderer
	renderer.SetupRenderer();
	//Load Icon
	icon.loadFromFile(iconPath);
	//Set Icon
	window.setIcon(32, 32, icon.getPixelsPtr());
}

//Gets the window size
sf::Vector2u Window::GetWindowSize() {
	return windowSize;
}

//Gets the SFML Renderwindow
sf::RenderWindow& Window::GetWindow() {
	return window;
}

//Gets the Render class
Renderer& Window::GetRenderer() {
	return renderer;
}
