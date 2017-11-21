#include "Collider.h"
#include "Scene.h"
#include "SceneManager.h"

using namespace BC;

//Constructor
Collider::Collider(const sf::Transformable& transform) : Transformable(transform) {
	//Dynamic casting
	spriteCast = dynamic_cast<const sf::Sprite*>(&transform);

	//If dynamic casting then set colliderObjectType
	if (spriteCast) {
		colliderObjectType = ColliderObjectType::Sprite;
	}
	else {
		//Dynamic casting
		textCast = dynamic_cast<const sf::Text*>(&transform);

		//If dynamic casting then set colliderObjectType
		if (textCast) {
			colliderObjectType = ColliderObjectType::Text;
		}
	}
	
}

//Destructor
Collider::~Collider() {
	std::cout << "bier " << GameObject->Name << std::endl;
}

//Override Start method from base Component class
void Collider::Start() {
	Component::Start();
}

//Override Update method from base Component class
void Collider::Update(float deltaTime) {
	Component::Update(deltaTime);

	FindCollideableObjects();
}

//Finds all the colliders in the scene
void Collider::FindCollideableObjects() {	
	//For every GameObject in the active scene
	for (auto it = SceneManager::GetActiveScene().GameObjects.begin(); it != SceneManager::GetActiveScene().GameObjects.end(); it++) {
		//For every Component on a GameObject
		for (auto it2 = it->second->Components.begin(); it2 != it->second->Components.end(); it2++) {
			//Dynamic cast collider
			Collider* collider = dynamic_cast<Collider*>(it2->second);

			//If dynamic cast is correctly casted
			if (collider) {
				//If collider is not equal to this collider
				//and if the Component is enabled
				if (collider != this && it2->second->Enabled) {
					//Make iterator and try to find this object in already existing map
					std::map<Collider*, ColliderData*>::iterator it;
					it = CollideableObjects.find(collider);

					//If the object is not found in the map
					//Make a new ColliderData struct for the collider and add both to the map
					if (it == CollideableObjects.end()) {
						ColliderData* colData = new ColliderData(false, false);
						CollideableObjects.insert(std::pair<Collider*, ColliderData*>(collider, colData));
					}
				}
			}
		}
	}
}

//Gets the object attached to this collider
const sf::Transformable& Collider::GetCollidingObject() {
	return Transformable;
}

//Gets the object attached to this collider
ColliderObjectType& Collider::GetColliderObjectType() {
	return colliderObjectType;
}

//Gets the collider type of the colliding object
const sf::Sprite& Collider::GetSpriteCast() {
	return *spriteCast;
}

//Gets the casted text type of the collider object
const sf::Text& Collider::GetTextCast() {
	return *textCast;
}
