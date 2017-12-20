#include "SceneManager.h"
#include "Game.h"
#include "BaseComponents.hpp"
#include "ReflectorBeam.h"
#include "MirrorManager.h"

SceneManager* SceneManager::instance = 0;

Scene* SceneManager::currentScene;
std::map<int, Scene*> SceneManager::scenes;
int SceneManager::sceneIndexAmount;

//Constructor
SceneManager::SceneManager() {

}

//Destructor
SceneManager::~SceneManager() {

}

//Static Get Method
SceneManager* SceneManager::GetInstance() {
	if (instance == 0) {
		instance = new SceneManager();
		instance->renderer = &Game::GetInstance()->GetWindowClass().GetRenderer();
	}

	return instance;
}

//Load a scene specified by a scene index
bool SceneManager::LoadScene(int sceneIndex) {
	bool canLoad = false;
	Scene* lastScene = nullptr;
	//Quit previous Scene
	if (currentScene != nullptr) {
		lastScene = currentScene;
		currentScene->Quit();
	}
	
	//For every scene, if index of that scene is equal to parameter,
	//set new currentScene
	if (!scenes.empty()) {
		for (auto it = scenes.begin(); it != scenes.end(); it++) {
			if (it->second != nullptr) {
				if (it->second->SceneIndex == sceneIndex) {
					currentScene = it->second;
					canLoad = true;
				}
			}
		}
	}

	//If new currentScene is succesfully transferred than
	//run setup, start and awake method of new scene
	//Reset the last scene that was loaded
	//Finally return out of function
	if (canLoad) {
		currentScene->Setup();
		currentScene->Awake();
		currentScene->Start();

		//If there is a last scene
		if (lastScene) {
			//Reset the last scene
			GetInstance()->ResetScene(lastScene);
		}
			
		return true;
	}
	else {
		std::cout << "Scene with index " << sceneIndex << " not found" << std::endl;
		return false;
	}
}

//Load a scene specified by a scene name
bool SceneManager::LoadScene(std::string sceneName) {
	bool canLoad = false;
	Scene* lastScene = nullptr;
	//Quit previous Scene
	if (currentScene != nullptr) {
		lastScene = currentScene;
		currentScene->Quit();
	}

	//For every scene, if the scene name of that scene is equal to parameter,
	//set new currentScene
	for (auto it = scenes.begin(); it != scenes.end(); it++) {
		if (it->second->Name == sceneName) {
			currentScene = it->second;
			canLoad = true;
		}
	}

	//If new currentScene is succesfully transferred than
	//run setup, start and awake method of new scene
	//Finally return out of function
	if (canLoad) {
		currentScene->Setup();
		currentScene->Awake();
		currentScene->Start();

		//If there is a last scene
		if (lastScene) {
			//Reset the last scene
			GetInstance()->ResetScene(lastScene);
		}

		return true;
	}
	else {
		std::cout << "Scene with name " << sceneName << " not found" << std::endl;
		return false;
	}
}

//Gets the active scene
Scene& SceneManager::GetActiveScene() {
	return *currentScene;
}

//Gets the amount of scenes in the game
int SceneManager::GetSceneAmount() {
	return sceneIndexAmount;
}

//Gets a scene by the index specified as a parameter
Scene& SceneManager::GetSceneByIndex(int sceneIndex) {
	//For every scene, if the scene name of that scene is equal to parameter,
	//set new currentScene
	for (auto it = scenes.begin(); it != scenes.end(); it++) {
		if (it->second->SceneIndex == sceneIndex) {
			return *it->second;
		}
	}

	//Cout log that says that the scene can't be found
	std::cout << "Scene with index " << sceneIndex << " not found" << std::endl;
}

//Gets a scene by a name specified as a parameter
Scene& SceneManager::GetSceneByName(std::string sceneName) {
	//For every scene, if the scene name of that scene is equal to parameter,
	//set new currentScene
	for (auto it = scenes.begin(); it != scenes.end(); it++) {
		if (it->second->Name == sceneName) {
			return *it->second;
		}
	}

	//Cout log that says that the scene can't be found
	std::cout << "Scene with name " << sceneName << " not found" << std::endl;
}

//Start the SceneManager
void SceneManager::StartSceneManager() {
	LoadScene(0);
}

//Method that updates the current active scene
void SceneManager::UpdateCurrentScene(float deltaTime) {
	currentScene->Update(deltaTime);
	RenderCurrentScene();
}

//Method that renders the current active scene
void SceneManager::RenderCurrentScene() {
	//Call BeginDraw function of the renderer class
	renderer->BeginDraw();

	for (int i = 4; i >= 0; i--) {
		if (currentScene->OrderedGameObjects[i].size() > 0) {
			for (auto it = currentScene->OrderedGameObjects[i].begin(); it != currentScene->OrderedGameObjects[i].end(); it++) {
				if ((*it)->Components.size() > 0) {
					//for every Component in the GameObject
					for (auto it2 = (*it)->Components.begin(); it2 != (*it)->Components.end(); it2++) {
						//if Component is enabled
						if (it2->second != nullptr && it2->second->Enabled) {
							//dynamic sprite casting
							//dynamic sprite rendering
							BC::Sprite* sprite = dynamic_cast<BC::Sprite*>(it2->second);

							if (sprite) {
								renderer->Draw(*sprite);
							}

							BC::Text* text = dynamic_cast<BC::Text*>(it2->second);

							if (text) {
								renderer->Draw(*text);
							}

							BC::Button* button = dynamic_cast<BC::Button*>(it2->second);

							if (button) {
								renderer->Draw(button->GetCurrentButtonSprite());
							}

							ReflectorBeam* reflectorBeam = dynamic_cast<ReflectorBeam*>(it2->second);

							if (reflectorBeam) {
								renderer->Draw(reflectorBeam->GetLine(), 2, sf::Lines);
							}

							Mirror* mirror = dynamic_cast<Mirror*>(it2->second);

							if (mirror) {
								if (mirror->GetLine()) {
									renderer->Draw(mirror->GetLine(), 2, sf::Lines);
								}
							}

							//Comment out if you want the box collider to show up when playing the game for testing purposes
							/*
							BC::BoxCollider* boxCollider = dynamic_cast<BC::BoxCollider*>(it2->second);

							if (boxCollider) {
							renderer->Draw(boxCollider->GetBoxCollider());
							}
							*/
						}
					}
				}
				
			}
		}
	}

	//Call EndDraw function of the renderer class	
	renderer->EndDraw();
}

//Reset method to reset a scene
void SceneManager::ResetScene(Scene* scene) {
	//Get Scene index of parameter scene
	int lastSceneIndex = scene->SceneIndex;

	//Local Iterator
	std::map<int, Scene*>::iterator LocalIt;
	//For every scene
	for (auto it = scenes.begin(); it != scenes.end(); it++) {
		//If scene name is equal to iterator scene name
		//set local iterator
		if (it->second->Name == scene->Name) {
			LocalIt = it;
		}
	}

	//If parameter scene has a certain name
	//erase from scenes map
	//call destructor of that scene
	//make a new scene scene
	//set scene index to be the last index
	//which is the index the scene lived in previously
	if (scene->Name == "MenuScene") {
		scenes.erase(LocalIt);
		menuSceneClass.~MenuScene();
		new (&menuSceneClass) MenuScene("MenuScene");
		menuSceneClass.SceneIndex = lastSceneIndex;
	}
	if (scene->Name == "MainScene") {
		scenes.erase(LocalIt);
		mainSceneClass.~MainScene();
		new (&mainSceneClass) MainScene("MainScene");
		mainSceneClass.SceneIndex = lastSceneIndex;
	}
	if (scene->Name == "LevelSelectScene") {
		scenes.erase(LocalIt);
		levelSelectScene.~LevelSelectScene();
		new (&levelSelectScene) LevelSelectScene("LevelSelectScene");
		levelSelectScene.SceneIndex = lastSceneIndex;
	}
	if (scene->Name == "CreditsScene") {
		scenes.erase(LocalIt);
		creditsSceneClass.~creditsSceneClass();
		new (&creditsSceneClass) CreditsScene("CreditsScene");
		creditsSceneClass.SceneIndex = lastSceneIndex;
	}
	if (scene->Name == "ShopScene") {
		scenes.erase(LocalIt);
		shopSceneClass.~shopSceneClass();
		new (&shopSceneClass) ShopScene("ShopScene");
		shopSceneClass.SceneIndex = lastSceneIndex;
	}
}

//Adds scene to list of scenes
void SceneManager::AddSceneToSceneManager(Scene* scene) {
	scenes.insert(std::pair<int, Scene*>(sceneIndexAmount, scene));
	scene->SceneIndex = sceneIndexAmount;
	sceneIndexAmount++;
}
