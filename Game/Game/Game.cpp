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
	sceneManager = SceneManager::GetInstance();
	singletonIndex = 0;
}

//Destructor
Game::~Game() {

}

//Main Start function that runs in the whole game
void Game::Start() {
	//Creates window with custom values
	Window::CreateWindow(sf::Vector2u(500, 800), "Prism", "../Assets/Art/Icon/Icon.png");
	//Start SceneManager method that loads the first scene
	sceneManager->StartSceneManager();
	//Setup input
	Input::SetupInput();
}

//Main Update function that runs in the whole game
void Game::Update() {
	//Set the deltaTime which is going to be passed troughout the whole game
	DeltaTime = clock.restart().asSeconds();
	//Call Update method of SceneManager which calls the Update method of the current Scene
	sceneManager->UpdateCurrentScene(DeltaTime);
	//call Update PollEvent method
	Input::UpdatePollEvent(DeltaTime);
}

//Gets SceneManager method
SceneManager& Game::GetSceneManager() {
	return *sceneManager;
}