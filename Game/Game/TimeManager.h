#pragma once

#include <iostream>
#include <string>

#include "Component.h"
#include "BaseComponents.hpp"

class TimeManager : public Component {
public:
	TimeManager();
	~TimeManager();

	void Start();
	void Update(float deltaTime);

private:
	sf::Time clock;
	int minutes;

	BC::Text* timeText;
};

