#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <map>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"
#include "GameObject.h"
#include "BaseComponents.hpp"

#include "Mirror.h"

//Manager for the mirrors
class MirrorManager : public Component {
public:
	//Constructor
	MirrorManager(BC::Button* addMirrorButton);
	//Destructor
	~MirrorManager();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

	//Adds a mirror
	void AddMirror();

	//Returns if a mirror is being moved
	bool IsMovingAMirror();

	//Gets the mirror map
	std::map<int, GameObject*>& GetMirrors();
	//Gets the current active mirror
	GameObject* GetCurrentMirror();

private:
	//Local current mirror
	GameObject* currentMirror;

	//Map of mirrors
	std::map<int, GameObject*> mirrors;
	//Index of map with mirrors
	int mirrorIndex;

	//Local add mirror button pointer
	BC::Button* localAddMirrorButton;
};
