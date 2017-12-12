#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"
#include "GameObject.h"
#include "BaseComponents.hpp"

//Mirror class
class Mirror : public Component {
public:
	//Constructor
	Mirror();
	//Destructor
	~Mirror();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

	//Get line
	sf::Vertex* GetLine();
	
	//Get can move
	bool CanMove();

private:
	//Determine if you can move this mirror
	bool canMove;

	//Speed to rotate with
	float rotateSpeed;

	//Reflect against line
	sf::Vertex* reflectLine = new sf::Vertex[2];
	//Vector of lines to ignore (backside and left, right side)
	std::vector<sf::Vertex*> ignoreLines;
};
