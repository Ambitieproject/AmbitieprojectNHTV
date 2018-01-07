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
#include "ReflectorBeamManager.h"
#include "MirrorManager.h"

//Include and use for making use of the Modern JSON library from nlohmann
//For more information go to the json hpp file 
#include "json.hpp"
using json = nlohmann::json;

//Level struct with values needed for a level to be contructed
struct Level {
	//Level int
	int level;

	//Vector with positions of the lasers
	std::vector<sf::Vector2f> LaserPositions;
	//Vector with rotations of the lasers
	std::vector<float> LaserRotations;
	
	//Count of minimum mirrors needed to complete a level
	int MirrorsNeededCount;
	
	//Vector with positions for blocking mirrors, if there are any
	std::vector<sf::Vector2f> BlockingMirrorsPositions;
	//Vector with rotations for blocking mirrors, if there are any
	std::vector<float> BlockingMirrorsRotations;
};

//Class that loads a level
class LevelLoader : public Component {
public:
	//Constructor
	LevelLoader(ReflectorBeamManager* reflectorBeamManager, MirrorManager* mirrorManager);
	//Destructor
	~LevelLoader();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

private:
	//Loads the data from a level
	void LoadCurrentLevelData();
	//Get JSON data and put it inside a Level object
	void SetLevelData(const json& j, Level& level, int iterator);

private:
	//Local current level holder
	Level currentLevel;

	//ReflectorBeamManager pointer
	ReflectorBeamManager* reflectorBeamManager;
	//MirrorManager pointer
	MirrorManager* mirrorManager;
};

