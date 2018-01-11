#pragma once

#include "Collider.h"

// * File:   collision.h
// * Authors: Nick Koirala(original version), ahnonay(SFML2 compatibility)
// *
// * Collision Detection and handling class
// * For SFML2.
// * Website: https://github.com/SFML/SFML/wiki/Source:-Simple-Collision-Detection-for-SFML-2

class OrientedBoundingBox // Used in the BoundingBoxTest
{
public:
	OrientedBoundingBox(const sf::RectangleShape& Object) // Calculate the four points of the OBB from a transformed (scaled, rotated...) sprite
	{
		sf::Transform trans = Object.getTransform();
		sf::IntRect local = Object.getTextureRect();
		Points[0] = trans.transformPoint(0, 0);
		Points[1] = trans.transformPoint((int)local.width, 0);
		Points[2] = trans.transformPoint((int)local.width, (int)local.height);
		Points[3] = trans.transformPoint(0, (int)local.height);
	}

	sf::Vector2f Points[4];

	void ProjectOntoAxis(const sf::Vector2f& Axis, float& Min, float& Max) // Project all four points of the OBB onto the given axis and return the dotproducts of the two outermost points
	{
		Min = (Points[0].x*Axis.x + Points[0].y*Axis.y);
		Max = Min;
		for (int j = 1; j<4; j++)
		{
			float Projection = (Points[j].x*Axis.x + Points[j].y*Axis.y);

			if (Projection<Min)
				Min = Projection;
			if (Projection>Max)
				Max = Projection;
		}
	}
};

//Namespace Base Component
namespace BC {
	//Box collider class
	class BoxCollider : public Collider {
	public:
		//Constructor with values to be added for a Collider to be created
		BoxCollider(const sf::Transformable& transform, sf::Vector2f originOffset, sf::Vector2f scaleOffset);
		//Destructor
		~BoxCollider();

		//Override Start method from base Component class
		void Start();
		//Override Update method from base Component class
		void Update(float deltaTime);

		//Collide method that returns the Collider that is colliding with this object when in the begin overlap state
		Collider* OnBeginOverlap();
		//Collide method that returns the Collider that is colliding with this object when in the stay overlap state
		Collider* OnStayOverlap();
		//Collide method that returns the Collider that is colliding with this object when in the end overlap state
		Collider* OnEndOverlap();

		//Returns the state of the mouse being over the object
		bool OnMouseEnter();
		//Returns the state of a specific mouse button being pressed on the object
		bool OnMouseDown(sf::Mouse::Button mouseButton);
		//Returns the state of the mouse exciting the object
		bool OnMouseExit();

		//Gets the box collider
		sf::RectangleShape& GetBoxCollider();
		
		//Bounding box test
		bool CheckBoundingBox(const sf::RectangleShape& Object1, const sf::RectangleShape& Object2);

	private:
		//The box collider
		sf::RectangleShape boxCollider;

		//Offset of the origin
		sf::Vector2f originOffset;
		//Offset of the scale
		sf::Vector2f scaleOffset;

		//Bool to check if mouse is overlapping
		bool isMouseOverlapping;
		//Bool to check if mouse is down
		bool isMouseDown;
	};
}
