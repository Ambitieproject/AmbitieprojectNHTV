#include "SceneManager.h"
#include "Game.h"

SceneManager* SceneManager::instance = 0;

Scene* SceneManager::currentScene;
std::map<int, Scene*> SceneManager::scenes;
int SceneManager::sceneIndexAmount;

//Constructor
SceneManager::SceneManager() {

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
	//Quit previous Scene
	currentScene->Quit();

	//For every scene, if index of that scene is equal to parameter,
	//set new currentScene
	for (auto it = scenes.begin(); it != scenes.end(); it++) {
		if (it->second->SceneIndex == sceneIndex) {
			currentScene = it->second;
			canLoad = true;
		}
	}

	//If new currentScene is succesfully transferred than
	//run start function of new scene
	//Finally return out of function
	if (canLoad) {
		currentScene->Start();
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
	//Quit previous Scene
	currentScene->Quit();

	//For every scene, if the scene name of that scene is equal to parameter,
	//set new currentScene
	for (auto it = scenes.begin(); it != scenes.end(); it++) {
		if (it->second->Name == sceneName) {
			currentScene = it->second;
			canLoad = true;
		}
	}

	//If new currentScene is succesfully transferred than
	//run start function of new scene
	//Finally return out of function
	if (canLoad) {
		currentScene->Start();
		return true;
	}
	else {
		std::cout << "Scene with name " << sceneName << " not found" << std::endl;
		return false;
	}
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

//Destructor
SceneManager::~SceneManager() {
	
}

void SceneManager::StartSceneManager() {
	currentScene = static_cast<Scene*>(&exampleScene);
	currentScene->Start();
}

//Method that updates the current active scene
void SceneManager::UpdateCurrentScene(float deltaTime) {
	//currentScene->Update(deltaTime);
	//RenderCurrentScene();
}

//Method that renders the current active scene
void SceneManager::RenderCurrentScene() {
	//Call BeginDraw function of the renderer class
	renderer->BeginDraw();

	//for every GameObject in the scene
	for (auto it = currentScene->GameObjects.begin(); it != currentScene->GameObjects.end(); it++) {
		//if GameObject is active
		if (it->second->Active) {
			//for every Component in the GameObject
			for (auto it2 = it->second->Components.begin(); it2 != it->second->Components.end(); it2++) {
				//if Component is enabled
				if (it2->second->Enabled) {
					//RENDER STUFF
				}
			}
		}
		
	}

	//Call EndDraw function of the renderer class	
	renderer->EndDraw();
}

//Adds scene to list of scenes
void SceneManager::AddSceneToSceneManager(Scene* scene) {
	scenes.insert(std::pair<int, Scene*>(sceneIndexAmount, scene));
	scene->SceneIndex = sceneIndexAmount;
	sceneIndexAmount++;
}
