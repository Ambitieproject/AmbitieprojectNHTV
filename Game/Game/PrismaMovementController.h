#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"
#include "BaseComponents.hpp"

#include "ColorManager.h"

class PrismaMovementController : public Component {
public:
	PrismaMovementController(BC::Sprite* prismaSprite);
	~PrismaMovementController();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

	bool IsMovingLeft();
	bool IsMovingRight();

	//Gets the current prism color
	sf::Color& GetCurrentPrismColor();

private:
	BC::Sprite* prisma;

	int rotateSpeed;

	bool isMovingLeft;
	bool isMovingRight;

	//Index that holds the current prisma color selected
	int currentPrismaColorIndex;
	//sf::Color that holds the current prisma color selected
	sf::Color currentPrismaColor;

	//ColorManager reference
	ColorManager* colorManager;
};

