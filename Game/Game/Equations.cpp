#include "Equations.h"

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

//Checks if two line given as parameters are colliding
bool Equations::LineCollide(sf::Vector2f p1, sf::Vector2f direction, sf::Vector2f c1, sf::Vector2f c2) {
	float pm = CalculateSlopeOfLine(p1, direction);
	//std::cout << "slope of laser: " << pm << std::endl;
	float pb = p1.y - pm * p1.x;
	
	float cm = CalculateSlopeOfLine(c1, c2);
	//std::cout << "slope of mirror: " << cm << std::endl;
	float cb = c1.y - cm * c1.x;

	//std::cout << pm << std::endl;
	//std::cout << cm << std::endl;

	if (pm != cm) {
		float x = (cb - pb) / (pm - cm);
		float y = cm * x + cb;
		
		if (x >= c1.x && x <= c2.x && y >= c1.y && y <= c2.y) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
