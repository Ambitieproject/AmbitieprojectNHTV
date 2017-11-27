#pragma once

#include "Collider.h"

//Namespace Base Component
namespace BC {
	//Box collider class
	class BoxCollider : public Collider {
	public:
		//Constructor with values to be added for a Collider to be created
		BoxCollider(const sf::Transformable& transform);
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
		
	private:
		//The box collider
		sf::RectangleShape boxCollider;

		bool isMouseOverlapping;
		bool isMouseDown;
	};
}
