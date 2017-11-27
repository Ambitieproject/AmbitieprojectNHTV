#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Scene.h"
#include "BaseComponents.hpp"
#include "GameObject.h"

#include "PrismaMovementController.h"
#include "ReflectorBeam.h"
#include "MirrorManager.h"

class ExampleScene : public Scene {
public:
	ExampleScene(std::string sceneName);
	~ExampleScene();

	void Awake();
	void Start();
	void Update(float deltaTime);

private:
	GameObject GOPrisma = GameObject("Prisma", *this);
	BC::Sprite prismaSprite = BC::Sprite("../Assets/prisma.png");
	PrismaMovementController prisma = PrismaMovementController(&prismaSprite);


	GameObject GOReflectorBeamManager = GameObject("ReflectorBeamManager", *this);
	ReflectorBeam reflectorBeam = ReflectorBeam("../Assets/pixelWhite.png");

	GameObject GOMirrorManager = GameObject("MirrorManager", *this);
	MirrorManager mirrorManager = MirrorManager();

	std::vector<sf::Color> prismaColors;

	int currentPrismaColorIndex;
	sf::Color currentPrismaColor;
};
