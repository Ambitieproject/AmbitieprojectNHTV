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

	//Override Setup method from base Scene class
	void Setup();
	//Override Start method from base Scene class
	void Start();
	//Override Update method from base Scene class
	void Update(float deltaTime);

private:
	//UI Logo Holder
	GameObject GOUILogoHolder = GameObject("UILogoHolder", *this);
	//Logo prism sprite
	BC::Sprite logoPrism = BC::Sprite("../Assets/Prism.png");
	//Logo prism text sprite
	BC::Sprite logoPrismText = BC::Sprite("../Assets/Menu/PrismText.png");

	///Audio holder and components
	GameObject GOAudioHolder = GameObject("AudioHolder", *this);
	BC::Music* backgroundMusic = new BC::Music("../Assets/Audio/BackgroundMusic.wav");

	///UI Sound Holder and components
	GameObject GOUIAudioHolder = GameObject("UIAudioHolder", *this);
	BC::Sprite audioSwitchSprite = BC::Sprite("../Assets/Art/Images/SoundNotMutedImage.png");
	BC::BoxCollider audioSwitchBoxCollider = BC::BoxCollider(audioSwitchSprite, sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	sf::Texture audioTextureNotMuted;
	sf::Texture audioTextureMuted;

	//UI Button Holder
	GameObject GOUIButtonHolder = GameObject("UIButtonHolder", *this);
	//Start button
	BC::Button buttonStart = BC::Button("../Assets/Menu/Buttons/Start/ButtonStartIdle.png", "../Assets/Menu/Buttons/Start/ButtonStartHovered.png", "../Assets/Menu/Buttons/Start/ButtonStartPressed.png");
	//Shop button
	BC::Button buttonShop = BC::Button("../Assets/Menu/Buttons/Shop/ButtonShopIdle.png", "../Assets/Menu/Buttons/Shop/ButtonShopHovered.png", "../Assets/Menu/Buttons/Shop/ButtonShopPressed.png");
	//Credits button
	BC::Button buttonCredits = BC::Button("../Assets/Menu/Buttons/Credits/ButtonCreditsIdle.png", "../Assets/Menu/Buttons/Credits/ButtonCreditsHovered.png", "../Assets/Menu/Buttons/Credits/ButtonCreditsPressed.png");
	//Quit button
	BC::Button buttonQuit = BC::Button("../Assets/Menu/Buttons/Quit/ButtonQuitIdle.png", "../Assets/Menu/Buttons/Quit/ButtonQuitHovered.png", "../Assets/Menu/Buttons/Quit/ButtonQuitPressed.png");
	//List of menu buttons
	std::list<BC::Button*> menuButton;

	//UI Reference holder GameObject
	GameObject GOUIRefHolder = GameObject("RefHolder", *this);
	//Reference sprite
	BC::Sprite refSprite = BC::Sprite("../Assets/Menu/JP2017.png");
};
