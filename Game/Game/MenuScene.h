#pragma once

//Include Scene header so this class can inherit from Scene
#include "Scene.h"

//Include Base Components so I can make Components in this class
#include "BaseComponents.hpp"

//Menu Scene, Custom made Scene class
class MenuScene : public Scene {
public:
	//Constructor
	MenuScene(std::string sceneName);
	//Destructor
	~MenuScene();

	//Override Awake method from base Component class
	void Awake();
	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

private:
	//StartButton GameObject
	GameObject GOStartButton = GameObject("StartButton", *this);
	//QuitButton GameObject
	GameObject GOSQuitButton = GameObject("QuitButton", *this);

	///Button Components
	BC::Button startButton = BC::Button("../Assets/UI/STARTBUTTON/buttonStartNormal.png", "../Assets/UI/STARTBUTTON/buttonStartHighlighted.png", "../Assets/UI/STARTBUTTON/buttonStartPressed.png");
	BC::Button quitButton = BC::Button("../Assets/UI/QUITBUTTON/buttonQuitNormal.png", "../Assets/UI/QUITBUTTON/buttonQuitHighlighted.png", "../Assets/UI/QUITBUTTON/buttonQuitPressed.png");
};

