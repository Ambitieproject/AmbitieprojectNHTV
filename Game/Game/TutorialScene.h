#pragma once

#include <iostream>

//Include Scene header so this class can inherit from Scene
#include "Scene.h"

//Include Base Components so I can make Components in this class
#include "BaseComponents.hpp"

//Tutorial Scene, Custom made Scene class
class TutorialScene : public Scene {
public:
	//Constructor
	TutorialScene(std::string sceneName);
	//Destructor
	~TutorialScene();

	//Override Setup method from base Scene class
	void Setup();
	//Override Start method from base Scene class
	void Start();
	//Override Update method from base Scene class
	void Update(float deltaTime);

private:
	///Background holder GameObject and components
	GameObject GOBackgroundHolder = GameObject("BackgroundHolder", *this);
	BC::Sprite backgroundSprite = BC::Sprite("../Assets/Art/Tutorial/Tutorial.png");
};

