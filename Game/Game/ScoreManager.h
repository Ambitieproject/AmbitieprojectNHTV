#pragma once

#include <iostream>
#include <string>

#include "Component.h"
#include "BaseComponents.hpp"

//ScoreManager class that takes care of score
class ScoreManager : public Component {
public:
	//Constructor
	ScoreManager();
	//Destructor
	~ScoreManager();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

	//Adjusts score by a specific parameter
	int AdjustScore(int adjustment);

	//Gets the score
	int GetScore();

private:
	//Local score variable
	int score;

	//Pointer to score text variable
	BC::Text* scoreText = nullptr;
};

