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
	GOUIRefHolder.SetDrawIndex(0);

	//Adding components to UI AudioManager GameObject
	GOUIAudioHolder.AddComponent(&audioSwitchSprite);
	GOUIAudioHolder.AddComponent(&audioSwitchBoxCollider);

	//Adding components to UILogo holder GameObject
	GOUILogoHolder.AddComponent(&logoPrism);
	GOUILogoHolder.AddComponent(&logoPrismText);

	//Adding components to UIButton holder GameObject
	GOUIButtonHolder.AddComponent(&buttonStart);
	GOUIButtonHolder.AddComponent(&buttonShop);
	GOUIButtonHolder.AddComponent(&buttonCredits);
	GOUIButtonHolder.AddComponent(&buttonQuit);

	//Adding components to ref holder GameObject
	GOUIRefHolder.AddComponent(&refSprite);

	//Setting standard values for logoPrism
	logoPrism.setScale(0.4f, 0.4f);
	logoPrism.setOrigin(logoPrism.getTexture()->getSize().x / 2, logoPrism.getTexture()->getSize().y / 2);
	logoPrism.setPosition(Window::GetInstance()->GetWindowSize().x / 2, 220);

	//Setting standard values for logoPrismText
	logoPrismText.setScale(0.4f, 0.4f);
	logoPrismText.setOrigin(logoPrismText.getTexture()->getSize().x / 2, logoPrismText.getTexture()->getSize().y / 2);
	logoPrismText.setPosition(Window::GetInstance()->GetWindowSize().x / 2, logoPrism.getPosition().y + (logoPrismText.getTexture()->getSize().y));

	//Push back all the menu buttons
	menuButton.push_back(&buttonStart);
	menuButton.push_back(&buttonShop);
	menuButton.push_back(&buttonCredits);
	menuButton.push_back(&buttonQuit);

	//Set scale and position for every menu button
	for (auto it = menuButton.begin(); it != menuButton.end(); it++) {
		it._Ptr->_Myval->GetCurrentButtonSprite().setScale(0.4, 0.4f);
		it._Ptr->_Myval->GetCurrentButtonSprite().setPosition(80, 400);
	}

	//Set position of buttons
	buttonShop.GetCurrentButtonSprite().setPosition(buttonShop.GetCurrentButtonSprite().getPosition().x + buttonShop.GetCurrentButtonSprite().getTexture()->getSize().x / 2, buttonShop.GetCurrentButtonSprite().getPosition().y);
	buttonCredits.GetCurrentButtonSprite().setPosition(buttonCredits.GetCurrentButtonSprite().getPosition().x, buttonCredits.GetCurrentButtonSprite().getPosition().y + 60);
	buttonQuit.GetCurrentButtonSprite().setPosition(buttonQuit.GetCurrentButtonSprite().getPosition().x, buttonQuit.GetCurrentButtonSprite().getPosition().y + 60);
	buttonQuit.GetCurrentButtonSprite().setPosition(buttonQuit.GetCurrentButtonSprite().getPosition().x + buttonQuit.GetCurrentButtonSprite().getTexture()->getSize().x / 2, buttonQuit.GetCurrentButtonSprite().getPosition().y);

	//Setting standard values of refSprite
	refSprite.setScale(0.6f, 0.6f);
	refSprite.setOrigin(refSprite.getTexture()->getSize().x / 2, refSprite.getTexture()->getSize().y / 2);
	refSprite.setPosition(Window::GetInstance()->GetWindowSize().x / 2, Window::GetInstance()->GetWindowSize().y - 30);

	//Load audio textures
	audioTextureNotMuted.loadFromFile("../Assets/Art/Images/SoundNotMutedImage.png");
	audioTextureMuted.loadFromFile("../Assets/Art/Images/SoundMutedImage.png");

	//Setting standard values of audioSwitchSprite
	audioSwitchSprite.setTexture(audioTextureNotMuted);
	audioSwitchSprite.setScale(0.6f, 0.6f);
	audioSwitchSprite.setPosition(5, 5);
}

//Override Start method from base Scene class
void MenuScene::Start() {
	Scene::Start();

	BC::Music* audio = AudioManager::GetMusic("BackgroundMusic");

	if (!audio) {
		backgroundMusic->play();
		backgroundMusic->setLoop(true);
		AudioManager::AddMusic(*backgroundMusic, "BackgroundMusic");
		AudioManager::AddSound(*buttonClickSound, "ButtonClickSound");
	}
	else {
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
	if (buttonShop.IsClicked()) {
		//Load scene
		SceneManager::LoadScene(4);
		//Play click sound
		AudioManager::GetSound("ButtonClickSound")->play();
	}
	//Load scene if button is pressed
	if (buttonCredits.IsClicked()) {
		//Load scene
		SceneManager::LoadScene(3);
		//Play click sound
		AudioManager::GetSound("ButtonClickSound")->play();
	}
	//Quit game if quit button is pressed
	if (buttonQuit.IsClicked()) {
		//Set closed boolean
		Window::GetInstance()->IsClosed = true;
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
