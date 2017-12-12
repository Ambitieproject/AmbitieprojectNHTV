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
bool Equations::LineCollide(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f direction, sf::Vector2f c1, sf::Vector2f c2, Mirror& mirrorCollider) {
	float pm = CalculateSlopeOfLine(p1, direction);
	float pb = p1.y - pm * p1.x;
	
	float cm = CalculateSlopeOfLine(c1, c2);
	float cb = c1.y - cm * c1.x;

	if (pm != cm) {
		float x = (cb - pb) / (pm - cm);
		float y = cm * x + cb;

		if (mirrorCollider.gameObject->GetComponent<BC::BoxCollider>()->GetBoxCollider().getGlobalBounds().contains(sf::Vector2f(x,y))) {
			//line faced down
			if (p1.y < p2.y) {
				//line faced right
				if (p1.x < p2.x) {
					if (y >= p1.y && y <= p2.y && x >= p1.x && x <= p2.x) {
						mirrorCollider.pointOfIntersect = sf::Vector2f(x, y);
						return true;
					}
					else {
						return false;
					}
				}
				//line faced left
				else {
					if (y >= p1.y && y <= p2.y && x >= p2.x && x <= p1.x) {
						mirrorCollider.pointOfIntersect = sf::Vector2f(x, y);
						return true;
					}
					else {
						return false;
					}
				}
			}
			//line faced up
			else {
				//line faced right
				if (p1.x < p2.x) {
					if (y >= p2.y && y <= p1.y && x >= p1.x && x <= p2.x) {
						mirrorCollider.pointOfIntersect = sf::Vector2f(x, y);
						return true;
					}
					else {
						return false;
					}
				}
				//line faced left
				else {
					if (y >= p2.y && y <= p1.y && x >= p2.x && x <= p1.x) {
						mirrorCollider.pointOfIntersect = sf::Vector2f(x, y);
						return true;
					}
					else {
						return false;
					}
				}
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
