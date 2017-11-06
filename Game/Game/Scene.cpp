#include "Scene.h"
#include "SceneManager.h"

//Constructor
Scene::Scene(std::string sceneName) {
	//Set Scene Name equal to parameter
	Name = sceneName;
	//Add scene to scene list in SceneManager
	SceneManager::AddSceneToSceneManager(this);
	//Reset gameObject index
	gameObjectLayerIndex = 0;
}

//Destructor
Scene::~Scene() {

}

//Initialization method that runs all the nessesary code to setup a scene
void Scene::Init() {
	
}

//Virtual Start Method of a scene that can be overwritten in a supper class
void Scene::Start() {
	
}

//Virtual Update Method of a scene that can be overwritten in a supper class
void Scene::Update(float deltaTime) {
	//For every GameObject in the scene
	for (auto objects = GameObjects.begin(); objects != GameObjects.end(); objects++) {
		//if GameObject is active
		if (objects->second->Active) {
			objects->second->Update(deltaTime);
		}
	}
	
}

//Virutal Quit Method of a scene that can be overwritten in a supper class
void Scene::Quit() {
	
}

//Adds a given GameObject to the list of GameObjects in the scene
void Scene::AddToGameObjectList(GameObject* gameObject) {
	GameObjects.insert(std::pair<int, GameObject*>(gameObjectLayerIndex, gameObject));
	gameObjectLayerIndex++;
}

//Finds a GameObject by name
GameObject* Scene::FindGameObjectByName(std::string gameObjectName) {
	for (auto it = GameObjects.begin(); it != GameObjects.end(); it++) {
		if (it->second->Name == gameObjectName) {
			return it->second;
		}
	}

	return nullptr;
}