#pragma once

#include <iostream>
#include <map>

//Include sprite class
#include "Sprite.h"

//Use Basic Components namespace
using namespace BC;

//enum that holds different types of objects a colliding type can be
enum ColliderObjectType {
	Sprite,
	Shape,
	Text,
	None
};

//Collider data struct that holds collider data for every colliding object
struct ColliderData {
public:
	//Constructor
	ColliderData(bool beginOverlap, bool endOverlap) : BeginOverlap(beginOverlap), EndOverlap(EndOverlap) {}

	//Begin overlap callback bool
	bool BeginOverlap;
	//End overlap callback bool
	bool EndOverlap;
};

//Namespace Base Component
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
		const sf::Transformable& GetCollidingObject();

		//Gets the collider type of the colliding object
		ColliderObjectType& GetColliderObjectType();

		//Gets the casted sprite type of the collider object
		const sf::Sprite& GetSpriteCast();
		//Gets the casted text type of the collider object
		const sf::Text& GetTextCast();

	public:
		//Map of all the collideable objects in the scene
		std::map<Collider*, ColliderData*> CollideableObjects;

		//Colliding object pointer
		Collider* CollidingObject;

		std::string ColliderTag;

	private:
		//Local collide transform variable
		const sf::Transformable& Transformable;

		//Enum that holds the type of the colliding object
		ColliderObjectType colliderObjectType;

		//The casted sprite type pointer of the colliding object
		const sf::Sprite* spriteCast = nullptr;
		//The casted text type pointer of the colliding object
		const sf::Text* textCast = nullptr;
	};
};

