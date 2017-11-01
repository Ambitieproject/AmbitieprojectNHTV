#include "SceneManager.h"
#include "Game.h"

//Constructor
SceneManager::SceneManager() {
	//currentScene = static_cast<Scene*>(&mainScene);
	currentScene->Start();
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
	currentScene->Update(deltaTime);
	RenderCurrentScene();
}

//Method that renders the current active scene
void SceneManager::RenderCurrentScene() {
	//Call BeginDraw function of the window class
	window->BeginDraw();

	/*
	for (auto it = currentScene->GameObjects.begin(); it != currentScene->GameObjects.end(); it++) {
		for (auto it2 = it->second->Components.begin(); it2 != it->second->Components.end(); it2++) {

			//dynamic sprite casting
			//dynamic sprite rendering
			JE::Sprite* sprite = dynamic_cast<JE::Sprite*>(it2->second);

			if (sprite) {
				window->Draw(sprite->GetSprite());
			}

			JE::Text* text = dynamic_cast<JE::Text*>(it2->second);

			if (text) {
				window->Draw(text->GetText());
			}
		}
	}
	*/

	//Call EndDraw function of the window class	
	window->EndDraw();
}