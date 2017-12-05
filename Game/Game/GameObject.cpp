#include "GameObject.h"
#include "Scene.h"


//Constructor that sets the name of scene of this gameobject
GameObject::GameObject(std::string name, Scene& scene, int drawIndex) : Name(name), scene(scene), drawIndex(drawIndex) {
	componentIndex = 0;
	//Add this gameobject to the list of gameobjects in the scene
	scene.AddToGameObjectList(this);
	//set state of GameObject to active by default
	Active = true;
}

//Destructor
GameObject::~GameObject() {
	//For every Component on this GameObject
	for (auto objects = Components.begin(); objects != Components.end(); objects++) {
		//Destruct the component
		objects->second->~Component();
	}
}

//Start method of GameObject
void GameObject::Start() {
	//For every Component on this GameObject
	for (auto objects = Components.begin(); objects != Components.end(); objects++) {
		//if GameObject is active
		if (objects->second->Enabled) {
			objects->second->Awake();
		}
	}

	//For every Component on this GameObject
	for (auto objects = Components.begin(); objects != Components.end(); objects++) {
		//if GameObject is active
		if (objects->second->Enabled) {
			objects->second->Start();
		}
	}
}

//Update method of GameObject
void GameObject::Update(float deltaTime) {
	//For every Component on this GameObject
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
	//Set Component layer index
	component->GameObjectLayerIndex = componentIndex;
	//Increase component index
	componentIndex++;
	//Set component's GameObject value to be equal to this GameObject
	component->gameObject = this;
}

//Gets the current Scene where this GameObject lives in
Scene & GameObject::GetScene() {
	return scene;
}