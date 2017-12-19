#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"
#include "GameObject.h"

#include "BaseComponents.hpp"
#include "FileReadWrite.h"

#include "json.hpp"

using json = nlohmann::json;

struct Level {
	int level;
	std::vector<sf::Vector2f> Positions;
	std::vector<float> Rotations;
	int MirrorsNeededCount;
};

class LevelLoader : public Component {
public:
	//Constructor
	LevelLoader();
	//Destructor
	~LevelLoader();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

private:
	void LoadCurrentLevelData();

private:
	Level currentLevel;
};

