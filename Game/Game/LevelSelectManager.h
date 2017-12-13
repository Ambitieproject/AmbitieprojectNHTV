#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <map>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"
#include "GameObject.h"

#include "BaseComponents.hpp"
//Manager class that takes care of managing the level selecting
class LevelSelectManager : public Component {
public:
	//Constructor
	LevelSelectManager();
	//Destructor
	~LevelSelectManager();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

	//Returns the state of level selected
	bool HasSelectedLevel();

	//Gets the current selected level number
	int GetCurrentSelectedLevel();

private:
	//Creates level buttons
	void CreateLevelButtons();

private:
	//Font used in level select
	BC::Font font = BC::Font("../Assets/Fonts/Myriad Pro Regular.ttf");

	//Map of different level buttons
	std::map<int, BC::Button*> levelButtons;

	//Current level number
	int currentSelectedLevel;

	//Has selected a level
	bool hasSelectedLevel;
};

