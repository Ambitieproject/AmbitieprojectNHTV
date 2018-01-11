#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

//Include Base Components
#include "BaseComponents.hpp"

//Define the number of PI
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

	//Creates a direction vector from a rotation
	static sf::Vector2f CreateDirectionFromRotation(float rotation);

	//Checks if two line given as parameters are colliding
	static sf::Vector2f LineCollide(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f direction, sf::Vector2f c1, sf::Vector2f c2, BC::Sprite& mirrorCollider);

private:
	//Point of intersection
	static sf::Vector2f pointOfIntersection;
};

