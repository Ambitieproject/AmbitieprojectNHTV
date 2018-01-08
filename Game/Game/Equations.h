#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

#include "BaseComponents.hpp"

#define PI 3.14159265

//Class that holds methods for equations
class Equations {
public:
	//Constructor
	Equations();
	//Destructor
	~Equations();

	//Calculates slope of one line
	static float CalculateSlopeOfLine(sf::Vector2f p1, sf::Vector2f p2);

	static sf::Vector2f CreateDirectionFromRotation(float rotation);

	//Checks if two line given as parameters are colliding
	static sf::Vector2f LineCollide(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f direction, sf::Vector2f c1, sf::Vector2f c2, BC::Sprite& mirrorCollider);
	static sf::Vector2f pointOfIntersection;
};

