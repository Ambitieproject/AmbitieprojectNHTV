#include "GameObject.h"
#include "Scene.h"


//Constructor that sets the name of scene of this gameobject
GameObject::GameObject(std::string name, Scene& scene) : Name(name), scene(scene) {
	componentIndex = 0;
	//Add this gameobject to the list of gameobjects in the scene
	scene.AddToGameObjectList(this);
}

GameObject::~GameObject() {
}

//Adds a component to this gameobject given as a parameter
void GameObject::AddComponent(Component* component) {
	//Insert component as a pair into the component map
	Components.insert(std::pair<int, Component*>(componentIndex, component));
	//Increase component index
	componentIndex++;
}


Scene & GameObject::GetScene()
{
	return scene;
}