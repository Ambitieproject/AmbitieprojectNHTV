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

//Virtual Awake Method of a scene that can be overwritten in a supper class 
void Scene::Awake() {

}

//Virtual Start Method of a scene that can be overwritten in a supper class
void Scene::Start() {
	//For every GameObject in the scene
	for (auto objects = GameObjects.begin(); objects != GameObjects.end(); objects++) {
		//if GameObject is active
		if (objects->second->Active) {
			objects->second->Start();
		}
	}
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
	gameObject->GameObjectSceneIndex = gameObjectLayerIndex;
	gameObjectLayerIndex++;
	std::cout << "asdfaaf" << std::endl;
}

//Destroys a specified GameObject
bool Scene::DestroyGameObject(GameObject* gameObject) {
	//Make iterator and try to find the GameObject
	std::map<int, GameObject*>::iterator it;
	it = GameObjects.find(gameObject->GameObjectSceneIndex);

	//If found destruct it else cout message
	if (it != GameObjects.end()) {
		GameObjects.erase(it);
		gameObject->~GameObject();
		return true;
	}
	else {
		std::cout << "Could not delete GameObject " << gameObject->Name << std::endl;
		return false;
	}

	return false;
}

//Destroys a specified Component
bool Scene::DestroyComponent(Component* component) {
	//Make iterator and try to find the Component 
	//while going through all the GameObject's Component map
	std::map<int, Component*>::iterator it;

	//Bool to determine if component is found
	bool found = false;

	//For length of GameObjects map size
	for (auto it2 = GameObjects.begin(); it2 != GameObjects.end(); it2++) {
		//If found is still false / not found
		if (!found) {
			//Set iterator to find component in map
			it = it2->second->Components.find(component->GameObjectLayerIndex);

			//If found set found to true 
			if (it != it2->second->Components.end()) {
				found = true;
			}
		}
	}

	//If found deconstruct Component else cout and return false
	if (found) {
		it->second->~Component();
		return true;
	}
	else {
		std::cout << "Could not delete Component " << component << std::endl;
		return false;
	}
}

//Finds a GameObject by name
GameObject* Scene::FindGameObjectByName(std::string gameObjectName) {
	//For every GameObject in the scene check if name is equal to the parameter's specified name
	//if so return the GameObject else return nullptr
	for (auto it = GameObjects.begin(); it != GameObjects.end(); it++) {
		if (it->second->Name == gameObjectName) {
			return it->second;
		}
	}

	return nullptr;
}