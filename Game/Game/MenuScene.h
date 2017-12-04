#pragma once

#include <iostream>
#include <string>

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
	//UI Logo Holder
	GameObject GOUILogoHolder = GameObject("UILogoHolder", *this);
	//Logo prism sprite
	BC::Sprite logoPrism = BC::Sprite("../Assets/Prism.png");
	//Logo prism text sprite
	BC::Sprite logoPrismText = BC::Sprite("../Assets/Menu/PrismText.png");

	//UI Sound Holder
	GameObject GOUIAudioHolder = GameObject("UIAudioHolder", *this);

	//UI Button Holder
	GameObject GOUIButtonHolder = GameObject("GOUIButtonHolder", *this);
	//Start button
	BC::Button buttonStart = BC::Button("../Assets/Menu/Buttons/Start/ButtonStartIdle.png", "../Assets/Menu/Buttons/Start/ButtonStartHovered.png", "../Assets/Menu/Buttons/Start/ButtonStartPressed.png");
	//Shop button
	BC::Button buttonShop = BC::Button("../Assets/Menu/Buttons/Shop/ButtonShopIdle.png", "../Assets/Menu/Buttons/Shop/ButtonShopHovered.png", "../Assets/Menu/Buttons/Shop/ButtonShopPressed.png");
	//Score button
	BC::Button buttonScore = BC::Button("../Assets/Menu/Buttons/Score/ButtonScoreIdle.png", "../Assets/Menu/Buttons/Score/ButtonScoreHovered.png", "../Assets/Menu/Buttons/Score/ButtonScorePressed.png");
	//Quit button
	BC::Button buttonQuit = BC::Button("../Assets/Menu/Buttons/Quit/ButtonQuitIdle.png", "../Assets/Menu/Buttons/Quit/ButtonQuitHovered.png", "../Assets/Menu/Buttons/Quit/ButtonQuitPressed.png");
	//List of menu buttons
	std::list<BC::Button*> menuButton;

	//UI Reference holder GameObject
	GameObject GOUIRefHolder = GameObject("GORefHolder", *this);
	//Reference sprite
	BC::Sprite refSprite = BC::Sprite("../Assets/Menu/JP2017.png");
};

