#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Scene.h"
#include "BaseComponents.hpp"
#include "GameObject.h"

#include "PrismaMovementController.h"
#include "ReflectorBeam.h"

class ExampleScene : public Scene {
public:
	ExampleScene(std::string sceneName);
	~ExampleScene();

	void Awake();
	void Start();
	void Update(float deltaTime);

private:
	GameObject GOPrisma = GameObject("Prisma", *this);
	BC::Sprite prismaSprite = BC::Sprite("../Assets/prisma.jpg");

	PrismaMovementController prisma = PrismaMovementController(&prismaSprite);

	GameObject GOReflectorBeamManager = GameObject("ReflectorBeamManager", *this);
	ReflectorBeam reflectorBeam = ReflectorBeam("../Assets/prisma.jpg");

	std::vector<sf::Color> prismaColors;

	int currentPrismaColorIndex;
	sf::Color currentPrismaColor;
};
