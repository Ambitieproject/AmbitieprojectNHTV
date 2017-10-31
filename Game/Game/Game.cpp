#include "Game.h"

Game* Game::instance = 0;

//Static Get Method
Game* Game::GetInstance() {
	if (instance == 0) {
		instance = new Game();
	}

	return instance;
}

//Constructor
Game::Game() {

}

//Destructor
Game::~Game() {
}

//Main Start function that runs in the whole game
void Game::Start() {
	//Creates window with custom values
	window.Intit(sf::Vector2u(300, 800), "Laser Space");
}

//Main Update function that runs in the whole game
void Game::Update() {
	DeltaTime = clock.restart().asSeconds();

	//sceneManager.UpdateCurrentScene(DeltaTime);
	//input.UpdatePollEvent();
}

//Gets Window class method
RenderWindow& Game::GetWindowClass()
{
	return window;
}
