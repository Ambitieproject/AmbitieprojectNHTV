#include "MenuScene.h"
#include "Window.h"
#include "SceneManager.h"
#include "Window.h"
#include "Game.h"

//Constructor
MenuScene::MenuScene(std::string sceneName) : Scene(sceneName) {

}

//Destructor
MenuScene::~MenuScene() {

}

//Override Setup method from base Scene class
void MenuScene::Setup() {
	Scene::Setup();

	//Setting drawing indexes of GameObjects
	GOUILogoHolder.SetDrawIndex(0);
	GOUIAudioHolder.SetDrawIndex(0);
	GOUIButtonHolder.SetDrawIndex(0);
	GOBackgroundHolder.SetDrawIndex(1);

	//Adding components to Background holder GameObject
	GOBackgroundHolder.AddComponent(&backgroundSprite);

	//Adding components to UI AudioManager GameObject
	GOUIAudioHolder.AddComponent(&audioSwitchSprite);
	GOUIAudioHolder.AddComponent(&audioSwitchBoxCollider);

	//Adding components to UILogo holder GameObject
	GOUILogoHolder.AddComponent(&logoPrism);

	//Adding components to UIButton holder GameObject
	GOUIButtonHolder.AddComponent(&buttonStart);
	GOUIButtonHolder.AddComponent(&buttonShopt);
	GOUIButtonHolder.AddComponent(&buttonCreditss);
	GOUIButtonHolder.AddComponent(&buttonQuits);

	//Setting standard values for logoPrism
	logoPrism.setScale(0.4f, 0.4f);
	logoPrism.setOrigin(logoPrism.getTexture()->getSize().x / 2, logoPrism.getTexture()->getSize().y / 2);
	logoPrism.setPosition(Window::GetWindowSize().x / 2, 220);

	//Push back all the menu buttons
	menuButton.push_back(&buttonStart);
	menuButton.push_back(&buttonShopt);
	menuButton.push_back(&buttonCreditss);
	menuButton.push_back(&buttonQuits);

	//Set scale and position for every menu button
	for (auto it = menuButton.begin(); it != menuButton.end(); it++) {
		it._Ptr->_Myval->GetCurrentButtonSprite().setScale(0.4, 0.4f);
		it._Ptr->_Myval->GetCurrentButtonSprite().setPosition(80, 400);
	}

	//Set position of buttons
	buttonShopt.GetCurrentButtonSprite().setPosition(buttonShopt.GetCurrentButtonSprite().getPosition().x + buttonShopt.GetCurrentButtonSprite().getTexture()->getSize().x / 2, buttonShopt.GetCurrentButtonSprite().getPosition().y);
	buttonCreditss.GetCurrentButtonSprite().setPosition(buttonCreditss.GetCurrentButtonSprite().getPosition().x, buttonCreditss.GetCurrentButtonSprite().getPosition().y + 60);
	buttonQuits.GetCurrentButtonSprite().setPosition(buttonQuits.GetCurrentButtonSprite().getPosition().x, buttonQuits.GetCurrentButtonSprite().getPosition().y + 60);
	buttonQuits.GetCurrentButtonSprite().setPosition(buttonQuits.GetCurrentButtonSprite().getPosition().x + buttonQuits.GetCurrentButtonSprite().getTexture()->getSize().x / 2, buttonQuits.GetCurrentButtonSprite().getPosition().y);

	//Load audio textures
	audioTextureNotMuted.loadFromFile("../Assets/Art/Menu/SoundNotMutedImage.png");
	audioTextureMuted.loadFromFile("../Assets/Art/Menu/SoundMutedImage.png");

	//Setting standard values of audioSwitchSprite
	audioSwitchSprite.setTexture(audioTextureNotMuted);
	audioSwitchSprite.setScale(0.6f, 0.6f);
	audioSwitchSprite.setPosition(15, 730);
}

//Override Start method from base Scene class
void MenuScene::Start() {
	Scene::Start();

	//Get background audio
	BC::Music* audio = AudioManager::GetMusic("BackgroundMusic");

	//If audio does not yet live set values
	if (!audio) {
		backgroundMusic->play();
		backgroundMusic->setLoop(true);
		AudioManager::AddMusic(*backgroundMusic, "BackgroundMusic");
		AudioManager::AddSound(*buttonClickSound, "ButtonClickSound");
	}
	else {
		//If audio lives and volume of audio is 0
		if (audio->getVolume() == 0) {
			//Set texture
			audioSwitchSprite.setTexture(audioTextureMuted);
		}
		
	}
}

//Override Update method from base Scene class
void MenuScene::Update(float deltaTime) {
	Scene::Update(deltaTime);
	
	//Load scene if button is pressed
	if (buttonStart.IsClicked()) {
		//Load scene
		SceneManager::LoadScene(1);
		//Play click sound
		AudioManager::GetSound("ButtonClickSound")->play();
	}
	//Load scene if button is pressed
	if (buttonShopt.IsClicked()) {
		//Load scene
		SceneManager::LoadScene(4);
		//Play click sound
		AudioManager::GetSound("ButtonClickSound")->play();
	}
	//Load scene if button is pressed
	if (buttonCreditss.IsClicked()) {
		//Load scene
		SceneManager::LoadScene(3);
		//Play click sound
		AudioManager::GetSound("ButtonClickSound")->play();
	}
	//Quit game if quit button is pressed
	if (buttonQuits.IsClicked()) {
		//Set closed boolean
		Window::IsClosed = true;
		//Play click sound
		AudioManager::GetSound("ButtonClickSound")->play();
	}

	//If mouse is down on the audioSwitchSprite
	if (audioSwitchBoxCollider.OnMouseDown(sf::Mouse::Left)) {
		//If mouse key is pressed
		if (Input::GetMouseKeyPressed(sf::Mouse::Left)) {
			//Change sprite of audioSwitchSprite variable relative to witch sprite is active
			if (audioSwitchSprite.getTexture() == &audioTextureNotMuted) {
				//Set texture
				audioSwitchSprite.setTexture(audioTextureMuted);
				//Set volumes
				AudioManager::GetSound("ButtonClickSound")->setVolume(0);
				AudioManager::GetMusic("BackgroundMusic")->setVolume(0);
			}
			else {
				audioSwitchSprite.setTexture(audioTextureNotMuted);
				//Set texture
				backgroundMusic->setVolume(70.0f);
				//Set volumes
				AudioManager::GetSound("ButtonClickSound")->setVolume(70);
				AudioManager::GetMusic("BackgroundMusic")->setVolume(70);
				//Play click sound
				AudioManager::GetSound("ButtonClickSound")->play();
			}
		}
	}
}
