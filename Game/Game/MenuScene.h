#pragma once

#include <iostream>
#include <string>

//Include Audio manage accessibility
#include "AudioManager.h"

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

	//Override Setup method from base Scene class
	void Setup();
	//Override Start method from base Scene class
	void Start();
	//Override Update method from base Scene class
	void Update(float deltaTime);

private:
	//Background Holder
	GameObject GOBackgroundHolder = GameObject("BackgroundHolder", *this);
	//Background sprite
	BC::Sprite backgroundSprite = BC::Sprite("../Assets/Art/Menu/Background.png");


	//UI Logo Holder
	GameObject GOUILogoHolder = GameObject("UILogoHolder", *this);
	//Logo prism sprite
	BC::Sprite logoPrism = BC::Sprite("../Assets/Art/Menu/Logo.png");

	///Audio components
	BC::Music* backgroundMusic = new BC::Music("../Assets/Audio/BackgroundMusic.wav");
	BC::Sound* buttonClickForwardSound = new BC::Sound("../Assets/Audio/ButtonClickForward.wav");
	BC::Sound* buttonClickBackSound = new BC::Sound("../Assets/Audio/ButtonClickBack.wav");

	///UI Sound Holder and components
	GameObject GOUIAudioHolder = GameObject("UIAudioHolder", *this);
	BC::Sprite audioSwitchSprite = BC::Sprite("../Assets/Art/Menu/SoundNotMutedImage.png");
	BC::BoxCollider audioSwitchBoxCollider = BC::BoxCollider(audioSwitchSprite, sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	sf::Texture audioTextureNotMuted;
	sf::Texture audioTextureMuted;

	//UI Button Holder
	GameObject GOUIButtonHolder = GameObject("UIButtonHolder", *this);
	//Start button
	BC::Button buttonStart = BC::Button("../Assets/Art/Menu/Buttons/Start/ButtonStartIdle.png", "../Assets/Art/Menu/Buttons/Start/ButtonStartHovered.png", "../Assets/Art/Menu/Buttons/Start/ButtonStartPressed.png");
	//Shop button
	BC::Button buttonShop = BC::Button("../Assets/Art/Menu/Buttons/Shop/ButtonShopIdle.png", "../Assets/Art/Menu/Buttons/Shop/ButtonShopHovered.png", "../Assets/Art/Menu/Buttons/Shop/ButtonShopPressed.png");
	//Credits button
	BC::Button buttonCredits = BC::Button("../Assets/Art/Menu/Buttons/Credits/ButtonCreditsIdle.png", "../Assets/Art/Menu/Buttons/Credits/ButtonCreditsHovered.png", "../Assets/Art/Menu/Buttons/Credits/ButtonCreditsPressed.png");
	//Quit button
	BC::Button buttonQuit = BC::Button("../Assets/Art/Menu/Buttons/Quit/ButtonQuitIdle.png", "../Assets/Art/Menu/Buttons/Quit/ButtonQuitHovered.png", "../Assets/Art/Menu/Buttons/Quit/ButtonQuitPressed.png");
	//List of menu buttons
	std::vector<BC::Button*> menuButton;
};
