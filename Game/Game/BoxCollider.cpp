#include "BoxCollider.h"
#include "GameObject.h"



BoxCollider::BoxCollider(const sf::Transformable& transform) : Collider(transform) {
	
}


BoxCollider::~BoxCollider() {

}

void BoxCollider::Start() {
	Collider::Start();	

}

void BoxCollider::Update(float deltaTime) {
	Collider::Update(deltaTime);

	switch (GetColliderObjectType()) {
	case ColliderObjectType::Sprite:
		sf::Vector2f size = sf::Vector2f(GetSpriteCast().getTextureRect().width, GetSpriteCast().getTextureRect().height);
		boxCollider.setSize(size);
		boxCollider.setScale(GetSpriteCast().getScale());
		boxCollider.setPosition(GetSpriteCast().getPosition());
		break;
	}

	boxCollider.setFillColor(sf::Color::Red);
}

Collider* BoxCollider::OnBeginOverlap() {
	if (!IsColliding) {
		for (auto it = CollideableObjects.begin(); it != CollideableObjects.end(); it++) {
			BoxCollider* boxCol = dynamic_cast<BoxCollider*>(it._Ptr->_Myval);

			if (boxCol) {
				if (boxCol->boxCollider.getGlobalBounds().intersects(this->boxCollider.getGlobalBounds())) {
					IsColliding = true;
					collidingObject = it._Ptr->_Myval;
					return it._Ptr->_Myval;
				}
			}
		}
	}

	return nullptr;
}

Collider* BoxCollider::OnStayOverlap() {
	for (auto it = CollideableObjects.begin(); it != CollideableObjects.end(); it++) {
		BoxCollider* boxCol = dynamic_cast<BoxCollider*>(it._Ptr->_Myval);

		if (boxCol) {
			if (boxCol->boxCollider.getGlobalBounds().intersects(this->boxCollider.getGlobalBounds())) {
				return it._Ptr->_Myval;
			}
		}
	}

	return nullptr;
}

Collider* BoxCollider::OnEndOverlap() {
	if (IsColliding) {
		BoxCollider* boxCol = dynamic_cast<BoxCollider*>(collidingObject);

		if (!boxCol->boxCollider.getGlobalBounds().intersects(this->boxCollider.getGlobalBounds())) {
			IsColliding = false;
			return collidingObject;
		}

		return nullptr;
	}
	else {
		OnBeginOverlap();
		return nullptr;
	}
	return nullptr;
}

sf::RectangleShape& BoxCollider::GetBoxCollider() {
	return boxCollider;
}
