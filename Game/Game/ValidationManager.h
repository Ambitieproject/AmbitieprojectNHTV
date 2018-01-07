#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

//Include needed framework header files
#include "Component.h"
#include "Equations.h"
#include "BaseComponents.hpp"

//Include needed costum header files
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

	//Checks for validation
	bool Validate();

private:
	//Checks the laser count
	bool CheckLaserCountColor();
	
private:
	//Local validation bool
	bool validation;

	//Local validation sparkle image
	BC::Sprite* validatedSprakleImage;

	//Checker sprite
	BC::Sprite* checkerSprite;

	//Vector with the validation to be checked
	std::vector<sf::Color> activeValidationColors;

	//ReflectorBeamManager pointer
	ReflectorBeamManager* reflectorBeamManager;
};

