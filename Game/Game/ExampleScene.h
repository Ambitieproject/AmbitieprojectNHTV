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
#include "TimeManager.h"

class ExampleScene : public Scene {
public:
	ExampleScene(std::string sceneName);
	~ExampleScene();

	void Awake();
	void Start();
	void Update(float deltaTime);

private:
	BC::Font font = BC::Font("../Assets/Heroes Legend.ttf");

	GameObject GOPrisma = GameObject("Prisma", *this);
	BC::Sprite prismaSprite = BC::Sprite("../Assets/Prism.png");
	PrismaMovementController prisma = PrismaMovementController(&prismaSprite);

	GameObject GOReflectorBeamManager = GameObject("ReflectorBeamManager", *this);
	ReflectorBeamManager reflectorBeam = ReflectorBeamManager("../Assets/pixelWhite.png");

	GameObject GOMirrorManager = GameObject("MirrorManager", *this);
	MirrorManager mirrorManager = MirrorManager();

	GameObject GOTimeManager = GameObject("TimeManager", *this);
	BC::Sprite timeBackgroundSprite = BC::Sprite("../Assets/Level/TopCircle.png");
	BC::Text timeText = BC::Text(&font);
	TimeManager timeManager = TimeManager();

	GameObject GOUIBackgroundBars = GameObject("BackgroundBars", *this);
	BC::Sprite backgroundBarTop = BC::Sprite("../Assets/Level/TopAndDownBar.png");
	BC::Sprite backgroundBarBottom = BC::Sprite("../Assets/Level/TopAndDownBar.png");
};
