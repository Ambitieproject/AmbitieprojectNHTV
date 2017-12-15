#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"
#include "BaseComponents.hpp"

#include "ValidationManager.h"

//Game Manager
class GameFlowManager : public Component {
public:
	GameFlowManager();
	~GameFlowManager();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

private:
	bool IsGameOver();

	//ValidationManager reference
	ValidationManager* validationManager;
};

