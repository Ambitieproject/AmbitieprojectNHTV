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

//Override Awake method from base Component class
void MenuScene::Awake() {
	Scene::Awake();

	//Setting drawing indexes of GameObjects
	GOUILogoHolder.SetDrawIndex(0);
	GOUIAudioHolder.SetDrawIndex(0);
	GOUIButtonHolder.SetDrawIndex(0);
	GOUIRefHolder.SetDrawIndex(0);

	//Adding components to UILogo holder GameObject
	GOUILogoHolder.AddComponent(&logoPrism);
	GOUILogoHolder.AddComponent(&logoPrismText);

	//Adding components to UIButton holder GameObject
	GOUIButtonHolder.AddComponent(&buttonStart);
	GOUIButtonHolder.AddComponent(&buttonShop);
	GOUIButtonHolder.AddComponent(&buttonScore);
	GOUIButtonHolder.AddComponent(&buttonQuit);

	//Adding components to ref holder GameObject
	GOUIRefHolder.AddComponent(&refSprite);

	//Setting standard values of components
	logoPrism.setScale(0.4f, 0.4f);
	logoPrism.setOrigin(logoPrism.getTexture()->getSize().x / 2, logoPrism.getTexture()->getSize().y / 2);
	logoPrism.setPosition(Window::GetInstance()->GetWindowSize().x / 2, 220);

	logoPrismText.setScale(0.4f, 0.4f);
	logoPrismText.setOrigin(logoPrismText.getTexture()->getSize().x / 2, logoPrismText.getTexture()->getSize().y / 2);
	logoPrismText.setPosition(Window::GetInstance()->GetWindowSize().x / 2, logoPrism.getPosition().y + (logoPrismText.getTexture()->getSize().y));

	menuButton.push_back(&buttonStart);
	menuButton.push_back(&buttonShop);
	menuButton.push_back(&buttonScore);
	menuButton.push_back(&buttonQuit);

	for (auto it = menuButton.begin(); it != menuButton.end(); it++) {
		it._Ptr->_Myval->GetCurrentButtonSprite().setScale(0.4, 0.4f);
		it._Ptr->_Myval->GetCurrentButtonSprite().setPosition(80, 400);
	}

	buttonShop.GetCurrentButtonSprite().setPosition(buttonShop.GetCurrentButtonSprite().getPosition().x + buttonShop.GetCurrentButtonSprite().getTexture()->getSize().x / 2, buttonShop.GetCurrentButtonSprite().getPosition().y);
	buttonScore.GetCurrentButtonSprite().setPosition(buttonScore.GetCurrentButtonSprite().getPosition().x, buttonScore.GetCurrentButtonSprite().getPosition().y + 60);
	buttonQuit.GetCurrentButtonSprite().setPosition(buttonQuit.GetCurrentButtonSprite().getPosition().x, buttonQuit.GetCurrentButtonSprite().getPosition().y + 60);
	buttonQuit.GetCurrentButtonSprite().setPosition(buttonQuit.GetCurrentButtonSprite().getPosition().x + buttonQuit.GetCurrentButtonSprite().getTexture()->getSize().x / 2, buttonQuit.GetCurrentButtonSprite().getPosition().y);

	refSprite.setScale(0.6f, 0.6f);
	refSprite.setOrigin(refSprite.getTexture()->getSize().x / 2, refSprite.getTexture()->getSize().y / 2);
	refSprite.setPosition(Window::GetInstance()->GetWindowSize().x / 2, Window::GetInstance()->GetWindowSize().y - 30);
}

//Override Start method from base Component class
void MenuScene::Start() {
	Scene::Start();
}

//Override Update method from base Component class
void MenuScene::Update(float deltaTime) {
	Scene::Update(deltaTime);

	if (buttonStart.IsClicked()) {
		SceneManager::LoadScene(1);
	}
	if (buttonShop.IsClicked()) {

	}
	if (buttonScore.IsClicked()) {

	}
	if (buttonQuit.IsClicked()) {
		Window::GetInstance()->IsClosed = true;
	}
}
