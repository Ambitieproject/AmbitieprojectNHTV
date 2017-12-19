#pragma once

#include <iostream>
#include <string>

//Include Scene header so this class can inherit from Scene
#include "Scene.h"

//Include Base Components so I can make Components in this class
#include "BaseComponents.hpp"

#include "LevelSelectManager.h"
#include "FileReadWrite.h"

#include "json.hpp"
using json = nlohmann::json;

//LevelSelectScene Scene, Custom made Scene class
class LevelSelectScene : public Scene {
public:
	//Constructor
	LevelSelectScene(std::string sceneName);
	//Destructor
	~LevelSelectScene();

	//Override Awake method from base Component class
	void Awake();
	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

private:
	//BackgroundBars GameObject and components
	GameObject GOUIBackgroundBars = GameObject("BackgroundBars", *this);
	BC::Sprite backgroundBarTop = BC::Sprite("../Assets/Bar.png");
	BC::Sprite backgroundBarBottom = BC::Sprite("../Assets/Bar.png");

	//UIManager GameObject and components
	GameObject GOUIManager = GameObject("UIManager", *this);
	BC::Sprite levelSelectText = BC::Sprite("../Assets/LevelSelect/levelSelectText.png");
	LevelSelectManager levelSelectManager = LevelSelectManager();
	BC::Button buttonBack = BC::Button("../Assets/buttonBack.png");
};

