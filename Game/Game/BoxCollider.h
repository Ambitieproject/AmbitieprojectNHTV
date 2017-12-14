#pragma once

#include "Collider.h"

class OrientedBoundingBox // Used in the BoundingBoxTest
{
public:
	OrientedBoundingBox(const sf::RectangleShape& Object) // Calculate the four points of the OBB from a transformed (scaled, rotated...) sprite
	{
		sf::Transform trans = Object.getTransform();
		sf::IntRect local = Object.getTextureRect();
		Points[0] = trans.transformPoint(0.f, 0.f);
		Points[1] = trans.transformPoint(local.width, 0.f);
		Points[2] = trans.transformPoint(local.width, local.height);
		Points[3] = trans.transformPoint(0.f, local.height);
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

		bool OnMouseEnter();
		bool OnMouseDown(sf::Mouse::Button mouseButton);
		bool OnMouseExit();

		//Gets the box collider
		sf::RectangleShape& GetBoxCollider();
		
		bool CheckBoundingBox(const sf::RectangleShape& Object1, const sf::RectangleShape& Object2);

	private:
		//The box collider
		sf::RectangleShape boxCollider;

		sf::Vector2f originOffset;
		sf::Vector2f scaleOffset;

		bool isMouseOverlapping;
		bool isMouseDown;
	};
}
