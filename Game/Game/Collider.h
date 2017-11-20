#pragma once

#include <iostream>
#include <map>

#include "Sprite.h"

using namespace BC;

enum ColliderObjectType {
	Sprite,
	Shape,
	Text,
	None
};

struct ColliderData {
public:
	ColliderData(bool beginOverlap, bool endOverlap) : BeginOverlap(beginOverlap), EndOverlap(EndOverlap) {}

	bool BeginOverlap;
	bool EndOverlap;
};

namespace BC {
	//Base collider class
	class Collider : public Component {
	public:
		//Constructor with values to be added for a Collider to be created
		Collider(const sf::Transformable& transfrom);
		//Destructor
		~Collider();

		//Override Start method from base Component class
		void Start();
		//Override Update method from base Component class
		void Update(float deltaTime);

		//Finds all the colliders in the scene
		void FindCollideableObjects();

		//Gets the object attached to this collider
		const sf::Transformable& GetCollideObject();

		//Local collide transform variable
		const sf::Transformable& Transformable;

		ColliderObjectType& GetColliderObjectType();

		const sf::Sprite& GetSpriteCast();

		//Map of all the collideable objects in the scene
		std::map<Collider*, ColliderData*> CollideableObjects;

		bool IsColliding;

		Collider* collidingObject;

	private:
		ColliderObjectType colliderObjectType;

		const sf::Sprite* spriteCast = nullptr;
	};
};

