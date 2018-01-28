#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"
#include "GameObject.h"
#include "BaseComponents.hpp"

//Forward include the MirrorManager class
class MirrorManager;

//Mirror class
class Mirror : public Component {
public:
	//Constructor
	Mirror(MirrorManager* mirrorManager);
	//Destructor
	~Mirror();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

	//Moves the mirror
	void Move(float deltaTime);

	//Get line
	sf::Vertex* GetLine();
	
	void SetMoving(bool moveState);

	//Get the state of this mirror being moved
	bool IsMoving();

	//Get the state of the object being a static object
	bool IsStaticObject();

	//Set the state of the object being a static object
	void SetIsStaticObject(bool isStatic);

private:
	//Determine if you can move this mirror
	bool isMoving;

	//Is a static object
	bool isStaticObject;

	//Speed to rotate with
	float rotateSpeed;

	//Reflect against line
	sf::Vertex* reflectLine = new sf::Vertex[2];
	//Vector of lines to ignore (backside and left, right side)
	std::vector<sf::Vertex*> ignoreLines;

	//Pointer to the MirrorManager class
	MirrorManager* mirrorManager;
};
