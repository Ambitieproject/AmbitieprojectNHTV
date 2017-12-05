#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Scene.h"
#include "BaseComponents.hpp"
#include "GameObject.h"

#include "PrismaMovementController.h"
#include "ReflectorBeamManager.h"
#include "MirrorManager.h"

class ExampleScene : public Scene {
public:
	ExampleScene(std::string sceneName);
	~ExampleScene();

	void Awake();
	void Start();
	void Update(float deltaTime);

private:
	GameObject GOPrisma = GameObject("Prisma", *this, 1);
	BC::Sprite prismaSprite = BC::Sprite("../Assets/Prism.png");
	PrismaMovementController prisma = PrismaMovementController(&prismaSprite);

	GameObject GOReflectorBeamManager = GameObject("ReflectorBeamManager", *this, 1);
	ReflectorBeamManager reflectorBeam = ReflectorBeamManager("../Assets/pixelWhite.png");

	GameObject GOMirrorManager = GameObject("MirrorManager", *this, 1);
	MirrorManager mirrorManager = MirrorManager();

	GameObject GOUIBackgroundBars = GameObject("BackgroundBars", *this, 0);
	BC::Sprite backgroundBarTop = BC::Sprite("../Assets/Level/TopAndDownBar.png");
	BC::Sprite backgroundBarBottom = BC::Sprite("../Assets/Level/TopAndDownBar.png");
};
