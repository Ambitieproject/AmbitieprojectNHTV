#include "BoxCollider.h"
#include "GameObject.h"

//Constructor with values to be added for a Collider to be created
BoxCollider::BoxCollider(const sf::Transformable& transform) : Collider(transform) {
	
}

//Destructor
BoxCollider::~BoxCollider() {

}

//Override Start method from base Component class
void BoxCollider::Start() {
	Collider::Start();	

}

//Override Update method from base Component class
void BoxCollider::Update(float deltaTime) {
	Collider::Update(deltaTime);

	//Switch on the colliding type
	switch (GetColliderObjectType()) {
	case ColliderObjectType::Sprite:
		//Set box collider size, scale and position depending on the sprite casted object
		boxCollider.setSize(sf::Vector2f(GetSpriteCast().getTextureRect().width, GetSpriteCast().getTextureRect().height));
		boxCollider.setScale(GetSpriteCast().getScale());
		boxCollider.setPosition(GetSpriteCast().getPosition());
		break;
	}

	boxCollider.setFillColor(sf::Color::Red);
}

//Collide method that returns the Collider that is colliding with this object when in the begin overlap state
Collider* BoxCollider::OnBeginOverlap() {
	//For every collider object in the collider object map
	for (auto it = CollideableObjects.begin(); it != CollideableObjects.end(); it++) {
		//try to cast to BoxCollider;
		BoxCollider* boxCol = dynamic_cast<BoxCollider*>(it->first);

		if (boxCol) {
			//If BeginOverlap of Colliding object is false
			if (!it->second->BeginOverlap) {
				//If the objects intersect with each other return the intersecting object and set BeginOverlap value of that Collider object
				if (boxCol->boxCollider.getGlobalBounds().intersects(this->boxCollider.getGlobalBounds())) {
					it->second->BeginOverlap = true;
					return it->first;
				}
			}	
			else {
				//If the objects don't intersect with each set BeginOverlap value of that Collider object
				if (!boxCol->boxCollider.getGlobalBounds().intersects(this->boxCollider.getGlobalBounds())) {
					it->second->BeginOverlap = false;
					return nullptr;
				}
			}
		}
	}

	return nullptr;
}

//Collide method that returns the Collider that is colliding with this object when in the stay overlap state
Collider* BoxCollider::OnStayOverlap() {
	//For every collider object in the collider object map
	for (auto it = CollideableObjects.begin(); it != CollideableObjects.end(); it++) {
		//try to cast to BoxCollider;
		BoxCollider* boxCol = dynamic_cast<BoxCollider*>(it->first);

		if (boxCol) {
			//If the objects intersect with each other return the intersecting object
			if (boxCol->boxCollider.getGlobalBounds().intersects(this->boxCollider.getGlobalBounds())) {
				return it->first;
			}
		}
	}

	return nullptr;
}

//Collide method that returns the Collider that is colliding with this object when in the end overlap state
Collider* BoxCollider::OnEndOverlap() {
	//For every collider object in the collider object map
	for (auto it = CollideableObjects.begin(); it != CollideableObjects.end(); it++) {
		//try to cast to BoxCollider;
		BoxCollider* boxCol = dynamic_cast<BoxCollider*>(it->first);

		if (boxCol) {
			//If EndOverlap of Colliding object is false
			if (!it->second->EndOverlap) {
				//If the objects don't intersect with each other return the intersecting object and set EndOverlap value of that Collider object
				if (!boxCol->boxCollider.getGlobalBounds().intersects(this->boxCollider.getGlobalBounds())) {
					it->second->EndOverlap = true;
					return it->first;
				}
			}
			else {
				//If the objects intersect with each set EndOverlap value of that Collider object
				if (boxCol->boxCollider.getGlobalBounds().intersects(this->boxCollider.getGlobalBounds())) {
					it->second->EndOverlap = false;
					return nullptr;
				}
			}
		}
	}

	return nullptr;
}

//Gets the box collider
sf::RectangleShape& BoxCollider::GetBoxCollider() {
	return boxCollider;
}
