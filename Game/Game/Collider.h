#pragma once

#include <iostream>
#include <map>

#include "Sprite.h"

using namespace BC;

//Namespace Base Component
namespace BC {
	//Base collider class
	class Collider : public Component {
	public:
		//Constructor with values to be added for a Collider to be created
		Collider();
		//Destructor
		~Collider();

		//Override Start method from base Component class
		void Start();
		//Override Update method from base Component class
		void Update(float deltaTime);

		void FindCollideableObjects();

		///getters
		Sprite& GetSprite();

	public:
		std::map<int, Collider&> collideableObjects;
		int collideableObjectsIndex;

	private:
		Sprite& sprite;
	};
};

