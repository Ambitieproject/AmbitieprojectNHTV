#pragma once

#include <iostream>
#include <string>

#include "Component.h"
#include "BaseComponents.hpp"

#include "MirrorManager.h"
#include "TimeManager.h"

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

