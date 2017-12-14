#pragma once
#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"
#include "Equations.h"
#include "BaseComponents.hpp"

#include "ReflectorBeamManager.h"

//Manager for checking laser validation
class ValidationManager : public Component {
public:
	//Constructor
	ValidationManager(BC::Sprite* checkerSprite, ReflectorBeamManager* reflectorBeamManager);
	//Destructor
	~ValidationManager();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

private:
	BC::Sprite* checkerSprite;
	ReflectorBeamManager* reflectorBeamManager;
};

