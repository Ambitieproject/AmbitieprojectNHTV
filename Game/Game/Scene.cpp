#include "Scene.h"

//Constructor
Scene::Scene() {
	//Reset gameObject index
	gameObjectLayerIndex = 0;
}

//Destructor
Scene::~Scene() {

}

//Virtual Start Method of a scene that can be overwritten in a supper class
void Scene::Start() {

}

//Virtual Update Method of a scene that can be overwritten in a supper class
void Scene::Update(float deltaTime) {
	/*
	for (auto objects = GameObjects.begin(); objects != GameObjects.end(); objects++) {
		for (auto component = objects->second->Components.begin(); component != objects->second->Components.end(); component++) {
			component->second->Update(deltaTime);
		}
	}
	*/
}
/*

//Adds a given GameObject to the list of GameObjects in the scene
void Scene::AddToGameObjectList(GameObject* gameObject) {
	GameObjects.insert(std::pair<int, GameObject*>(gameObjectLayerIndex, gameObject));
	gameObjectLayerIndex++;
}
*/

/*
//Finds a GameObject by name
GameObject* Scene::FindGameObjectByName(std::string gameObjectName) {
	for (auto it = GameObjects.begin(); it != GameObjects.end(); it++) {
		if (it->second->Name == gameObjectName) {
			return it->second;
		}
	}

	return nullptr;
}
*/