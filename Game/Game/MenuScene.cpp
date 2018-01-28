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
	GOUIButtonHolder.AddComponent(&buttonShop);
	GOUIButtonHolder.AddComponent(&buttonCredits);
	GOUIButtonHolder.AddComponent(&buttonQuit);

	//Setting standard values for logoPrism
	logoPrism.setScale(0.4f, 0.4f);
	logoPrism.setOrigin(logoPrism.getTexture()->getSize().x / 2, logoPrism.getTexture()->getSize().y / 2);
	logoPrism.setPosition(Window::GetWindowSize().x / 2, 170);

	//Push back all the menu buttons
	menuButton.push_back(&buttonStart);
	menuButton.push_back(&buttonShop);
	menuButton.push_back(&buttonCredits);
	menuButton.push_back(&buttonQuit);

	//Set scale and position for every menu button
	for (int i = 0; i < menuButton.size(); i++) {
		menuButton[i]->GetCurrentButtonSprite().setScale(0.4, 0.4f);
		menuButton[i]->GetCurrentButtonSprite().setPosition(Window::GetWindowSize().x / 2 - 77.8f, 380);

		if (i != 0) {
			menuButton[i]->GetCurrentButtonSprite().setPosition(menuButton[i]->GetCurrentButtonSprite().getPosition().x, menuButton[i - 1]->GetCurrentButtonSprite().getPosition().y + 60);
		}
	}

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
		AudioManager::AddSound(*buttonClickForwardSound, "ButtonClickForwardSound");
		AudioManager::AddSound(*buttonClickBackSound, "ButtonClickBackSound");
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
		SceneManager::LoadScene(2);
		//Play click sound
		AudioManager::GetSound("ButtonClickForwardSound")->play();
	}
	//Load scene if button is pressed
	if (buttonShop.IsClicked()) {
		//Load scene
		SceneManager::LoadScene(5);
		//Play click sound
		AudioManager::GetSound("ButtonClickForwardSound")->play();
	}
	//Load scene if button is pressed
	if (buttonCredits.IsClicked()) {
		//Load scene
		SceneManager::LoadScene(4);
		//Play click sound
		AudioManager::GetSound("ButtonClickForwardSound")->play();
	}
	//Quit game if quit button is pressed
	if (buttonQuit.IsClicked()) {
		//Set closed boolean
		Window::IsClosed = true;
		//Play click sound
		AudioManager::GetSound("ButtonClickBackSound")->play();
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
				AudioManager::GetSound("ButtonClickForwardSound")->setVolume(0);
				AudioManager::GetSound("ButtonClickBackSound")->setVolume(0);
				AudioManager::GetMusic("BackgroundMusic")->setVolume(0);
			}
			else {
				audioSwitchSprite.setTexture(audioTextureNotMuted);
				//Set texture
				backgroundMusic->setVolume(70.0f);
				//Set volumes
				AudioManager::GetSound("ButtonClickForwardSound")->setVolume(70);
				AudioManager::GetSound("ButtonClickBackSound")->setVolume(70);
				AudioManager::GetMusic("BackgroundMusic")->setVolume(70);
				//Play click sound
				AudioManager::GetSound("ButtonClickForwardSound")->play();
			}
		}
	}
}
