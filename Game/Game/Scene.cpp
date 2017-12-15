#include "Scene.h"
#include "SceneManager.h"
#include "Game.h"

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
	GameObjects.clear();
}

//Initialization method that runs all the nessesary code to setup a scene
void Scene::Init() {
	
}

//Virtual Setup Method of a scene that can be overwritten in a supper class 
void Scene::Setup() {

}

//Virtual Awake Method of a scene that can be overwritten in a supper class 
void Scene::Awake() {
	canUpdate = true;

	//For every GameObject in the scene
	for (auto it = GameObjects.begin(); it != GameObjects.end(); it++) {
		//if GameObject is active
		if (it->second->Active) {
			it->second->Awake();
		}
	}

	//If singleton map has a bigger size then 0
	if (Game::GetInstance()->GetSingletons().size() > 0) {
		std::map<int, GameObject*> tempSingletonGameObjects = Game::GetInstance()->GetSingletons();
		//For every singleton GameObject in the scene
		for (auto it = tempSingletonGameObjects.begin(); it != tempSingletonGameObjects.end(); it++) {
			//if GameObject is active
			if (it->second->Active) {
				it->second->Awake();
			}
		}
	}
}

//Virtual Start Method of a scene that can be overwritten in a supper class
void Scene::Start() {
	//For every GameObject in the scene
	for (auto it = GameObjects.begin(); it != GameObjects.end(); it++) {
		//if GameObject is active
		if (it->second->Active) {
			it->second->Start();
		}
	}

	//If singleton map has a bigger size then 0
	if (Game::GetInstance()->GetSingletons().size() > 0) {
		std::map<int, GameObject*> tempSingletonGameObjects = Game::GetInstance()->GetSingletons();
		//For every singleton GameObject in the scene
		for (auto it = tempSingletonGameObjects.begin(); it != tempSingletonGameObjects.end(); it++) {
			//if GameObject is active
			if (it->second->Active) {
				it->second->Start();
			}
		}
	}
}

//Virtual Update Method of a scene that can be overwritten in a supper class
void Scene::Update(float deltaTime) {
	if (canUpdate) {
		//For every GameObject in the scene
		for (auto it = GameObjects.begin(); it != GameObjects.end();) {

			if (it->second != nullptr) {
				//if GameObject is active
				if (it->second->Active) {
					it->second->Update(deltaTime);
					it++;
				}
			}
			else {
				it = GameObjects.erase(it);
			}
		}

		//If singleton map has a bigger size then 0
		if (Game::GetInstance()->GetSingletons().size() > 0) {
			std::map<int, GameObject*> tempSingletonGameObjects = Game::GetInstance()->GetSingletons();
			//For every singleton GameObject in the scene
			for (auto it = tempSingletonGameObjects.begin(); it != tempSingletonGameObjects.end(); it++) {
				//if GameObject is active
				if (it->second->Active) {
					it->second->Update(deltaTime);
				}
			}
		}
	}
}

//Virutal Quit Method of a scene that can be overwritten in a supper class
void Scene::Quit() {
	canUpdate = false;
}

//Adds a given GameObject to the list of GameObjects in the scene
void Scene::AddToGameObjectList(GameObject* gameObject) {
	GameObjects.insert(std::pair<int, GameObject*>(gameObjectLayerIndex, gameObject));
	gameObject->GameObjectSceneIndex = gameObjectLayerIndex;
	gameObjectLayerIndex++;
}

//Destroys a specified GameObject
bool Scene::DestroyGameObject(GameObject* gameObject) {
	//Bool to determine if component is found
	bool found = false;
	//For length of GameObjects map size
	for (auto it = GameObjects.begin(); it != GameObjects.end(); it++) {
		if (!found) {
			//Set GameObject if it is not yet found
			if (it->second == gameObject) {
				found = true;
				it->second->~GameObject();
				it->second = nullptr;
			}
		}
	}
	//If found deconstruct GameObject else cout and return false
	if (found) {
		gameObject = nullptr;
		return true;
	}
	else {
		std::cout << "Could not delete GameObject " << gameObject->Name << std::endl;
		return false;
	}
}

//Destroys a specified Component
bool Scene::DestroyComponent(Component* component) {
	//Bool to determine if component is found
	bool found = false;
	//Component pointer to set component to
	Component* comp;
	//For length of GameObjects map size
	for (auto it = GameObjects.begin(); it != GameObjects.end(); it++) {
		//For length of Components in a GameObject map size
		for (auto it2 = it->second->Components.begin(); it2 != it->second->Components.end(); it2++) {
			//Set Component if it is not yet found
			if (!found) {
				if (it2->second == component) {
					comp = it2->second;
					found = true;
				}
			}
		}
	}
	//If found deconstruct Component else cout and return false
	if (found) {
		comp->~Component();
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
 