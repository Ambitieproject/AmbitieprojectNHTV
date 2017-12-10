#pragma once

#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>

#include "Component.h"
#include "BaseComponents.hpp"

//Class that takes care of managing colors
class ColorManager : public Component {
public:
	//Constructor
	ColorManager();
	//Destructor
	~ColorManager();

	//Override Awake method from base Component class
	void Awake();
	//Override Update method from base Component class
	void Update(float deltaTime);

	//Gets the colors
	std::vector<sf::Color>& GetColors();

private:
	//Color vector
	std::vector<sf::Color> colors;
};

