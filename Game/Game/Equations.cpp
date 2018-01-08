#include "Equations.h"
#include "BaseComponents.hpp"

sf::Vector2f Equations::pointOfIntersection;

//Constructor
Equations::Equations() {

}

//Destructor
Equations::~Equations() {

}

//Calculates slope of one line
float Equations::CalculateSlopeOfLine(sf::Vector2f p1, sf::Vector2f p2) {
	float y = p2.y - p1.y;
	float x = p2.x - p1.x;

	return y / x;
}

sf::Vector2f Equations::CreateDirectionFromRotation(float rotation) {
	float x = 0;
	float y = 0;

	x = sin(rotation * PI / 180);
	y = cos(rotation * PI / 180);
	y = -y;

	return sf::Vector2f(x, y);
}


//Checks if two line given as parameters are colliding
sf::Vector2f Equations::LineCollide(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f direction, sf::Vector2f c1, sf::Vector2f c2, BC::Sprite& mirrorCollider) {
	float pm = CalculateSlopeOfLine(p1, p1 + direction);
	float pb = p1.y - pm * p1.x;
	
	float cm = CalculateSlopeOfLine(c1, c2);
	float cb = c1.y - cm * c1.x;

	if (pm != cm) {
		float x = (cb - pb) / (pm - cm);
		float y = cm * x + cb;

		sf::Vector2f intersectPosition = sf::Vector2f(x, y);

		if (mirrorCollider.getGlobalBounds().contains(intersectPosition)) {

			sf::Vector2f diff = intersectPosition - p1;
			float length = sqrt((diff.x * diff.x) + (diff.y * diff.y));
			sf::Vector2f calc = sf::Vector2f(p1 + direction * length);

			int pixelIntersectX = (int)intersectPosition.x;
			int pixelIntersectY = (int)intersectPosition.y;

			int pixelCalcX = (int)calc.x;
			int pixelCalcY = (int)calc.y;

			if (pixelIntersectX == pixelCalcX && pixelIntersectY == pixelCalcY) {
				return intersectPosition;
			}
			else {
				return sf::Vector2f(-100, -100);
			}
			
		}
		else {
			return sf::Vector2f(-100, -100);
		}
	}
	else {
		return sf::Vector2f(-100, -100);
	}
}
