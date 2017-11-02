#include "SceneManager.h"
#include "Game.h"

SceneManager* SceneManager::instance = 0;

//Constructor
SceneManager::SceneManager() {
	//currentScene = static_cast<Scene*>(&mainScene);
	//currentScene->Start();
}
//Static Get Method
SceneManager* SceneManager::GetInstance() {
	if (instance == 0) {
		instance = new SceneManager();
	}

	return instance;
}

//Destructor
SceneManager::~SceneManager() {

}

//Sets references for the SceneManager to communicate
void SceneManager::Setup() {
	Game* game = Game::GetInstance();
	window = &game->GetWindowClass();
}

//Method that start the current active scene
void SceneManager::StartCurrentScene() {
	currentScene->Start();
}

//Method that updates the current active scene
void SceneManager::UpdateCurrentScene(float deltaTime) {
	//currentScene->Update(deltaTime);
	//RenderCurrentScene();
}

//Method that renders the current active scene
void SceneManager::RenderCurrentScene() {
	//Call BeginDraw function of the window class
	window->GetRenderer().BeginDraw();

	for (auto it = currentScene->GameObjects.begin(); it != currentScene->GameObjects.end(); it++) {
		for (auto it2 = it->second->Components.begin(); it2 != it->second->Components.end(); it2++) {
			
		}
	}
	

	//Call EndDraw function of the window class	
	window->GetRenderer().EndDraw();
}