#pragma once

#include "Component.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>

class Scene;

//Custom Object made to hold components and run them
class GameObject {
public:
	//Constructor with name and scene to indentify this gameobject with
	GameObject(std::string name, Scene& scene);

	//Destructor
	~GameObject();

	//Start method of GameObject
	void Start();
	//Update method of GameObject
	void Update(float deltaTime);

	//Adds a component to this gameobject given as a parameter
	void AddComponent(Component* component);

	//Gets the current Scene where this GameObject lives in
	Scene& GetScene();

	//Gets a component asked for and returns it as a type asked for
	template<class component = Component>
	component* GetComponent();

	//Gets components asked for and puts it out as a vector
	template<class component = Component>
	std::vector<component*> GetComponents();

public:
	//Name of gameobject
	std::string Name;

	//Map with components for this gameobject
	std::map<int, Component*> Components;

	//bool for getting and setting active state of this gameobject
	bool Active;

private:
	//Current scene where this gameobject lives in
	Scene& scene;

	//Index of how much components this gameobject has
	int componentIndex;

};

template<class component>
inline component* GameObject::GetComponent() {
	for (int i = 0; i < Components.size(); i++) {
		component* comp = dynamic_cast<component*>(Components[i]);

		if (comp) {
			return comp;
		}
	}
	return nullptr;
}

template<class component>
inline std::vector<component*> GameObject::GetComponents()
{
	std::vector<component*> components;

	for (int i = 0; i < Components.size(); i++) {
		component* comp = dynamic_cast<component*>(Components[i]);

		if (comp) {
			components.push_back(comp);
		}
	}

	return components;
}

