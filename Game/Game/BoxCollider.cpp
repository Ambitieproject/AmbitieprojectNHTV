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
	for (auto it = CollideableObjects.begin(); it != CollideableObjects.end(); it++) {
		BoxCollider* boxCol = dynamic_cast<BoxCollider*>(it->first);

		if (boxCol) {
			if (!it->second->BeginOverlap) {
				if (boxCol->boxCollider.getGlobalBounds().intersects(this->boxCollider.getGlobalBounds())) {
					it->second->BeginOverlap = true;
					return it->first;
				}
			}	
			else {
				if (!boxCol->boxCollider.getGlobalBounds().intersects(this->boxCollider.getGlobalBounds())) {
					it->second->BeginOverlap = false;
					return nullptr;
				}
			}
		}
	}

	return nullptr;
}

Collider* BoxCollider::OnStayOverlap() {
	for (auto it = CollideableObjects.begin(); it != CollideableObjects.end(); it++) {
		BoxCollider* boxCol = dynamic_cast<BoxCollider*>(it->first);

		if (boxCol) {
			if (boxCol->boxCollider.getGlobalBounds().intersects(this->boxCollider.getGlobalBounds())) {
				return it->first;
			}
		}
	}

	return nullptr;
}

Collider* BoxCollider::OnEndOverlap() {
	for (auto it = CollideableObjects.begin(); it != CollideableObjects.end(); it++) {
		BoxCollider* boxCol = dynamic_cast<BoxCollider*>(it->first);

		if (boxCol) {
			if (!it->second->EndOverlap) {
				if (!boxCol->boxCollider.getGlobalBounds().intersects(this->boxCollider.getGlobalBounds())) {
					it->second->EndOverlap = true;
					return it->first;
				}
			}
			else {
				if (boxCol->boxCollider.getGlobalBounds().intersects(this->boxCollider.getGlobalBounds())) {
					it->second->EndOverlap = false;
					return nullptr;
				}
			}
		}
	}

	return nullptr;
}

sf::RectangleShape& BoxCollider::GetBoxCollider() {
	return boxCollider;
}
