#pragma once

#include <iostream>
#include <string>

//Include Scene header so this class can inherit from Scene
#include "Scene.h"

//Include Base Components so I can make Components in this class
#include "BaseComponents.hpp"

//Credits Scene, Custom made Scene class
class CreditsScene : public Scene {
public:
	//Constructor
	CreditsScene(std::string sceneName);
	//Destructor
	~CreditsScene();

	//Override Setup method from base Scene class
	void Setup();
	//Override Start method from base Scene class
	void Start();
	//Override Update method from base Scene class
	void Update(float deltaTime);

private:
	///CreditManager GameObject and components
	GameObject GOcreditManager = GameObject("CreditManager", *this);
	BC::Sprite CreditSprite = BC::Sprite("../Assets/Credits/Credits.png");
};

