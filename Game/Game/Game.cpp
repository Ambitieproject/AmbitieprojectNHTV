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
	input = Input::GetInstance();
	sceneManager = SceneManager::GetInstance();
	window = Window::GetInstance();
}

//Destructor
Game::~Game() {
}

//Main Start function that runs in the whole game
void Game::Start() {
	//Creates window with custom values
	window->CreateWindow(sf::Vector2u(500, 800), "Laser Space");
	//Setup input so values are assigned the right way
	input->SetupInput();
	std::cout << &window << std::endl;
}

//Main Update function that runs in the whole game
void Game::Update() {
	//Set the deltaTime which is going to be passed troughout the whole game
	DeltaTime = clock.restart().asSeconds();
	//Call Update method of SceneManager which calls the Update method of the current Scene
	sceneManager->UpdateCurrentScene(DeltaTime);
	//call Update PollEvent method
	input->UpdatePollEvent();
}

//Gets Window class method
Window& Game::GetWindowClass() {
	return *window;
}

SceneManager & Game::GetSceneManager() {
	return *sceneManager;
}

//Gets InputManager Method
Input& Game::GetInputManager() {
	return *input;
}
