#include "GameObject.h"
#include "Scene.h"


//Constructor that sets the name of scene of this gameobject
GameObject::GameObject(std::string name, Scene& scene) : Name(name), scene(scene) {
	componentIndex = 0;
	//Add this gameobject to the list of gameobjects in the scene
	scene.AddToGameObjectList(this);
	//set state of GameObject to active by default
	Active = true;
}

//Destructor
GameObject::~GameObject() {

}

//Start method of GameObject
void GameObject::Start() {
	//For every Component in the scene
	for (auto objects = Components.begin(); objects != Components.end(); objects++) {
		//if GameObject is active
		if (objects->second->Enabled) {
			objects->second->Start();
		}
	}
}

//Update method of GameObject
void GameObject::Update(float deltaTime) {
	//For every Component in the scene
	for (auto objects = Components.begin(); objects != Components.end(); objects++) {
		//if GameObject is active
		if (objects->second->Enabled) {
			objects->second->Update(deltaTime);
		}
	}
}

//Adds a component to this gameobject given as a parameter
void GameObject::AddComponent(Component* component) {
	//Insert component as a pair into the component map
	Components.insert(std::pair<int, Component*>(componentIndex, component));
	//Increase component index
	componentIndex++;
	//Set component's GameObject value to be equal to this GameObject
	component->GameObject = this;
}


Scene & GameObject::GetScene() {
	return scene;
}