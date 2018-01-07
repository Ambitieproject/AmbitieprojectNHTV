#pragma once

#include <iostream>
#include <string>
#include <vector>

//Include needed framework header files
#include "Scene.h"
#include "BaseComponents.hpp"
#include "GameObject.h"

//Include needed costum header files
#include "ReflectorBeamManager.h"
#include "MirrorManager.h"
#include "TimeManager.h"
#include "ScoreManager.h"
#include "ShapeAssignmentManager.h"
#include "ValidationManager.h"
#include "GameFlowManager.h"
#include "LevelLoader.h"

//Main Scene, Custom made Scene class
class MainScene : public Scene {
public:
	//Constructor
	MainScene(std::string sceneName);
	//Destructor
	~MainScene();

	//Override Setup method from base Scene class
	void Setup();
	//Override Start method from base Scene class
	void Start();
	//Override Update method from base Scene class
	void Update(float deltaTime);

private:
	//Font used in this scene
	BC::Font font = BC::Font("../Assets/Fonts/Myriad Pro Regular.ttf");

	///Prisma GameObject and Components
	GameObject GOPrisma = GameObject("Prisma", *this);
	BC::Sprite prismaSprite = BC::Sprite("../Assets/Prism.png");
	BC::BoxCollider prismBoxCollider = BC::BoxCollider(prismaSprite, sf::Vector2f(0,0), sf::Vector2f(0,0));

	///ReflectorBeamManager GameObject and Components
	GameObject GOReflectorBeamManager = GameObject("ReflectorBeamManager", *this);
	ReflectorBeamManager reflectorBeam = ReflectorBeamManager();

	///UIManager GameObject and components
	GameObject GOUIManager = GameObject("GOUIManager", *this);
	BC::Sprite timeBackgroundSprite = BC::Sprite("../Assets/Level/TopCircle.png");
	BC::Text timeText = BC::Text(&font);
	BC::Button addMirrorButton = BC::Button("../Assets/Level/AddMirror.png");

	///BackgroundBars GameObject and components
	GameObject GOUIBackgroundBars = GameObject("BackgroundBars", *this);
	BC::Sprite backgroundBarTop = BC::Sprite("../Assets/Bar.png");

	///ValidationManager GameObject and Components
	GameObject GOValidationManager = GameObject("ValidationManager", *this);
	ValidationManager validationManager = ValidationManager(&prismaSprite, &reflectorBeam);

	///Game Manager GameObject
	GameObject GOGameManager = GameObject("GameManager", *this);
	GameFlowManager gameFlowManager = GameFlowManager(scoreManager, validationManager);
	ScoreManager scoreManager = ScoreManager(mirrorManager, timeManager);
	TimeManager timeManager = TimeManager();
	MirrorManager mirrorManager = MirrorManager(&addMirrorButton, &reflectorBeam);
	LevelLoader levelLoader = LevelLoader(&reflectorBeam, &mirrorManager);
};
