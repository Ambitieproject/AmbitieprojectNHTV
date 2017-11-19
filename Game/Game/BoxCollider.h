#pragma once

#include "Collider.h"

namespace BC {
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

		//Collide method that returns the transformable that collides with this collider
		Collider* OnBeginOverlap();
		Collider* OnStayOverlap();
		Collider* OnEndOverlap();

		sf::RectangleShape& GetBoxCollider();
		
	private:
		sf::RectangleShape boxCollider;
	};
}
