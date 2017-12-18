#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <map>

class Level {
public:
	Level();
	~Level();

public:
	int level;
	std::map<sf::Vector2f, float> laserPositions;
};

