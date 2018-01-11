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
	//Get y difference
	float y = p2.y - p1.y;
	//Get x difference
	float x = p2.x - p1.x;

	//Difide values by each other
	return y / x;
}

//Creates a direction vector from a rotation
sf::Vector2f Equations::CreateDirectionFromRotation(float rotation) {
	//Create x and y value
	float x = 0;
	float y = 0;

	//Get sinus of the rotation times PI divided by 180
	x = sin(rotation * PI / 180);
	//Get cosinus of the rotation times PI divided by 180
	y = cos(rotation * PI / 180);

	//transform y value
	y = -y;

	//Return new vector
	return sf::Vector2f(x, y);
}


//Checks if two line given as parameters are colliding
sf::Vector2f Equations::LineCollide(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f direction, sf::Vector2f c1, sf::Vector2f c2, BC::Sprite& mirrorCollider) {
	//Get slope of line 1
	float pm = CalculateSlopeOfLine(p1, p1 + direction);
	//Get b value of line 1
	float pb = p1.y - pm * p1.x;
	
	//Get slope of line 2
	float cm = CalculateSlopeOfLine(c1, c2);
	//Get b value of line 2
	float cb = c1.y - cm * c1.x;

	//If slope is not equal to each other because otherwise the lines are parallel
	if (pm != cm) {
		//Callculate x value
		float x = (cb - pb) / (pm - cm);
		//Calculate y value
		float y = cm * x + cb;

		//Get point of intersection in temp variable
		sf::Vector2f intersectPosition = sf::Vector2f(x, y);

		//If sorite collider contains the intersection point
		if (mirrorCollider.getGlobalBounds().contains(intersectPosition)) {

			//Get difference from intersectionPoint to the beginpoint of line 1
			sf::Vector2f diff = intersectPosition - p1;
			//Get length of difference
			float length = sqrt((diff.x * diff.x) + (diff.y * diff.y));
			//Calculate new vector point together with the calculated length and given direction of line 1
			sf::Vector2f calc = sf::Vector2f(p1 + direction * length);

			//Get x and y values of intersectionPoint as an int
			int pixelIntersectX = (int)intersectPosition.x;
			int pixelIntersectY = (int)intersectPosition.y;

			//Get x and y values of new calculated vector as an int
			int pixelCalcX = (int)calc.x;
			int pixelCalcY = (int)calc.y;

			//If points are equal to each other
			if (pixelIntersectX == pixelCalcX && pixelIntersectY == pixelCalcY) {
				//Return the intersection point
				return intersectPosition;
			}
			else {
				//Return a minus number which indicates the intersection point is not found
				return sf::Vector2f(-100, -100);
			}
			
		}
		else {
			//Return a minus number which indicates the intersection point is not found
			return sf::Vector2f(-100, -100);
		}
	}
	else {
		//Return a minus number which indicates the intersection point is not found
		return sf::Vector2f(-100, -100);
	}
}
