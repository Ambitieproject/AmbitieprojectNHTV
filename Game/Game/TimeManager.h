#pragma once

#include <iostream>
#include <string>

#include "Component.h"
#include "BaseComponents.hpp"

//TimeManager class
class TimeManager : public Component {
public:
	//Constructor
	TimeManager(int timeInSeconds);
	//Destructor
	~TimeManager();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

private:
	//Local minutes variable
	int minutes;
	//Local seconds variable
	int seconds;

	//Float that holds the totalTime
	float totalTime;

	//Determine if there can be counted
	bool canCount;

	//Pointer to the text which needs to be a counter
	BC::Text* timeText;
};

