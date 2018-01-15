#pragma once

#include <iostream>
#include <string>

//Include Audio manage accessibility
#include "AudioManager.h"

//Include Scene header so this class can inherit from Scene
#include "Scene.h"

//Include Base Components so I can make Components in this class
#include "BaseComponents.hpp"

//Include needed header files
#include "LevelSelectManager.h"
#include "FileReadWrite.h"

//Include and use for making use of the Modern JSON library from nlohmann
//For more information go to the json hpp file 
#include "json.hpp"
using json = nlohmann::json;

//LevelSelectScene Scene, Custom made Scene class
class LevelSelectScene : public Scene {
public:
	//Constructor
	LevelSelectScene(std::string sceneName);
	//Destructor
	~LevelSelectScene();

	//Override Setup method from base Scene class
	void Setup();
	//Override Start method from base Scene class
	void Start();
	//Override Update method from base Scene class
	void Update(float deltaTime);

private:
	///BackgroundBars GameObject and components
	GameObject GOUIBackgroundBars = GameObject("BackgroundBars", *this);
	BC::Sprite backgroundBarTop = BC::Sprite("../Assets/Bar.png");
	BC::Sprite backgroundBarBottom = BC::Sprite("../Assets/Bar.png");

	///UIManager GameObject and components
	GameObject GOUIManager = GameObject("UIManager", *this);
	BC::Sprite levelSelectText = BC::Sprite("../Assets/LevelSelect/levelSelectText.png");
	LevelSelectManager levelSelectManager = LevelSelectManager();
	BC::Button buttonBack = BC::Button("../Assets/buttonBack.png");
};

