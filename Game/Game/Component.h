#pragma once

//Include the files a component needs such as Input
#include "Input.h"

//Forward include GameObject class that lives in a higher hierachy level
class GameObject;

//Base component class that lives as a base for every component created in the game
class Component {
public:
	//Constructor
	Component();
	//Destructor
	virtual ~Component();

	//Awake method of this comopnent
	virtual void Awake();
	//Start method of this component
	virtual void Start();
	//Update method of this component
	virtual void Update(float deltaTime);

public:
	//Bool to determine if component is enabled
	bool Enabled;

	//Bool to determine if start method did already run
	bool DidStart;

	//Index of component in GameObject
	int GameObjectLayerIndex;

	//Pointer to the Component's GameObject
	GameObject* gameObject = nullptr;
};