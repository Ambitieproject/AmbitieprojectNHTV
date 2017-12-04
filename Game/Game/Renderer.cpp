#include "Renderer.h"
#include "Window.h"
#include "Game.h"
#include "Scene.h"

//Constructor
Renderer::Renderer() {
	
}

//Destructor
Renderer::~Renderer() {

}

//Sets the renderer up, does reference setup
void Renderer::SetupRenderer() {
	window = &Game::GetInstance()->GetWindowClass().GetWindow();
}

//Begin draw method
void Renderer::BeginDraw() {
	//Clears the window with a given color as a parameter
	window->clear(sf::Color(97,97,97,255));
}

//Draw method that draws a SFML Drawable
void Renderer::Draw(sf::Drawable& drawable) {
	//Draw a drawable to the window
	window->draw(drawable);
}

//End draw method
void Renderer::EndDraw() {
	//Display to the window
	window->display();
}
