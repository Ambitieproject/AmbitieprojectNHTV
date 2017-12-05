#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <map>
#include <vector>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"

#include "BaseComponents.hpp"
#include "MirrorManager.h"
#include "ReflectorBeam.h"
#include "PrismaMovementController.h"

class ReflectorBeamManager : public Component {
public:
	ReflectorBeamManager(std::string beamFilePath);
	~ReflectorBeamManager();

	void Start();
	void Update(float deltaTime);

	//Adds a beam with a position and rotation
	GameObject& AddBeam(sf::Vector2f position, float rotateAngel);
	
private:
	//Sets the colors of every beam
	void SetBeamColor();

private:
	std::string beamFilePath;

	std::map<int, GameObject*> beams;
	int beamIndex;

	//Prisma reference
	BC::Sprite* prisma;
	//MirrorManager reference
	MirrorManager* mirrorManager;
	//PrismaMovementController reference
	PrismaMovementController* prismaMovementController;

	//Color vector
	std::vector<sf::Color> prismaColors;
	//Index that holds the current prisma color selected
	int currentPrismaColorIndex;
	//sf::Color that holds the current prisma color selected
	sf::Color currentPrismaColor;
};

