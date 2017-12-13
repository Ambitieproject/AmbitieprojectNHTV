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
	window = Window::GetInstance();
}

//Destructor
Game::~Game() {

}

//Main Start function that runs in the whole game
void Game::Start() {
	//Creates window with custom values
	window->CreateWindow(sf::Vector2u(500, 800), "Laser Space");
	//Start SceneManager method that loads the first scene
	sceneManager->StartSceneManager();

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

//Makes a GameObject into a singleton
GameObject& Game::AddSingleton(GameObject& gameObject) {
	//Make temp pointer object that copies content of parameter GameObject
	GameObject* go = &gameObject;
	//Pushback the temp GameObject into the singleton vector
	singletons.push_back(go);
	//Return temp GameObject
	return *go;
}

//Gets an already made singleton GameObject
GameObject* Game::GetSingleton(std::string gameObjectName) {
	//Make temp pointer object that copies content of parameter GameObject
	GameObject* go;
	//Go through the Singletons
	for (int i = 0; i < singletons.size(); i++) {
		//If name of index Singleton is the same as the GameObjects name then return that GameObject
		if (singletons[i]->Name == gameObjectName) {
			return singletons[i];
		}
	}
	//If no match is found return nullptr
	return nullptr;
}

//Gets Window class method
Window& Game::GetWindowClass() {
	return *window;
}

//Gets SceneManager method
SceneManager& Game::GetSceneManager() {
	return *sceneManager;
}