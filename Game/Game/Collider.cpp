#include "Collider.h"
#include "Scene.h"
#include "SceneManager.h"

using namespace BC;

Collider::Collider(const sf::Transformable& transform) : Transformable(transform) {

	spriteCast = dynamic_cast<const sf::Sprite*>(&transform);

	if (spriteCast) {
		colliderObjectType = ColliderObjectType::Sprite;
	}

	IsColliding = false;
}


Collider::~Collider()
{
}

void Collider::Start() {
	Component::Start();
}

void Collider::Update(float deltaTime) {
	Component::Update(deltaTime);

	FindCollideableObjects();
}

void Collider::FindCollideableObjects() {
	CollideableObjects.clear();
	
	for (auto it = SceneManager::GetActiveScene().GameObjects.begin(); it != SceneManager::GetActiveScene().GameObjects.end(); it++) {
		for (auto it2 = it->second->Components.begin(); it2 != it->second->Components.end(); it2++) {
			Collider* collider = dynamic_cast<Collider*>(it2->second);

			if (collider) {
				if (collider != this) {
					CollideableObjects.push_back(collider);
				}
			}
		}
	}
}

//Gets the object attached to this collider
const sf::Transformable& Collider::GetCollideObject() {
	return Transformable;
}

ColliderObjectType& Collider::GetColliderObjectType() {
	return colliderObjectType;
}

const sf::Sprite& Collider::GetSpriteCast() {
	return *spriteCast;
}
