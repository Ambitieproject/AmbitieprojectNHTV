#pragma once

#include <iostream>
#include <string>

//Include needed framework header files
#include "Component.h"
#include "BaseComponents.hpp"
#include "FileReadWrite.h"

//Include needed costum header files
#include "MirrorManager.h"
#include "TimeManager.h"

//Include and use for making use of the Modern JSON library from nlohmann
//For more information go to the json hpp file 
#include "json.hpp"
using json = nlohmann::json;

//ScoreManager class that takes care of score
class ScoreManager : public Component {
public:
	//Constructor
	ScoreManager(MirrorManager& mirrorManager, TimeManager& timeManager);
	//Destructor
	~ScoreManager();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

	//Gets the score
	int GetScore();

	//Gets the final score
	int GetFinalScore();

	//Gets the amount of mirrors used
	int GetMirrorsUsed();

	//Get extra mirrors from shop
	int GetExtraMirrorsFromShop();
	//Get extra time from shop
	int GetExtraTimeFromShop();

	//Get the maximum mirrors allowed in a level
	int GetMaximumMirrorsAllowed();

private:
	//Adjusts score by a specific parameter
	int AdjustScore(int adjustment);

private:
	//Local score variable
	int score;

	//Local max score variable
	int maxScore;

	//MirrorManager reference
	MirrorManager& mirrorManager;
	//TimeManager reference
	TimeManager& timeManager;
};

