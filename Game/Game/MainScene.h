#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Scene.h"
#include "BaseComponents.hpp"
#include "GameObject.h"

#include "ReflectorBeamManager.h"
#include "MirrorManager.h"
#include "TimeManager.h"
#include "ScoreManager.h"
#include "ShapeAssignmentManager.h"
#include "ColorManager.h"
#include "ValidationManager.h"

class MainScene : public Scene {
public:
	MainScene(std::string sceneName);
	~MainScene();

	void Setup();
	void Start();
	void Update(float deltaTime);

private:
	//Font used in this scene
	BC::Font font = BC::Font("../Assets/Fonts/Myriad Pro Regular.ttf");

	//Prisma GameObject and Components
	GameObject GOPrisma = GameObject("Prisma", *this);
	BC::Sprite prismaSprite = BC::Sprite("../Assets/Prism.png");
	BC::BoxCollider prismBoxCollider = BC::BoxCollider(prismaSprite, sf::Vector2f(0,0), sf::Vector2f(0,0));

	//ReflectorBeamManager GameObject and Components
	GameObject GOReflectorBeamManager = GameObject("ReflectorBeamManager", *this);
	ReflectorBeamManager reflectorBeam = ReflectorBeamManager();

	GameObject GOColorManager = GameObject("ColorManager", *this);
	ColorManager colorManager = ColorManager();

	//MirrorManager GameObject and Components
	GameObject GOMirrorManager = GameObject("MirrorManager", *this);
	MirrorManager mirrorManager = MirrorManager();

	//UIManager GameObject and components
	GameObject GOUIManager = GameObject("GOUIManager", *this);
	BC::Sprite timeBackgroundSprite = BC::Sprite("../Assets/Level/TopCircle.png");
	BC::Text timeText = BC::Text(&font);
	TimeManager timeManager = TimeManager();

	BC::Text scoreText = BC::Text(&font);
	BC::Text scoreTextStatic = BC::Text(&font);
	ScoreManager scoreManager = ScoreManager();

	BC::Button addMirrorButton = BC::Button("../Assets/Level/AddMirror.png");

	//BackgroundBars GameObject and components
	GameObject GOUIBackgroundBars = GameObject("BackgroundBars", *this);
	BC::Sprite backgroundBarTop = BC::Sprite("../Assets/Bar.png");

	//ValidationManager GameObject and Components
	GameObject GOValidationManager = GameObject("ValidationManager", *this);
	ValidationManager validationManager = ValidationManager(&prismaSprite, &reflectorBeam);
};
