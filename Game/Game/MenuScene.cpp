#include "MenuScene.h"
#include "Window.h"
#include "SceneManager.h"

//Constructor
MenuScene::MenuScene(std::string sceneName) : Scene(sceneName) {

}

//Destructor
MenuScene::~MenuScene()
{
}

//Override Awake method from base Component class
void MenuScene::Awake() {
	Scene::Awake();

	//Adding components to the GameObjects
	GOStartButton.AddComponent(&startButton);
	GOSQuitButton.AddComponent(&quitButton);
}

//Override Start method from base Component class
void MenuScene::Start() {
	//Set positions of buttons, relative to the window width and height
	startButton.GetCurrentButtonSprite().setOrigin(startButton.GetCurrentButtonSprite().getTexture()->getSize().x / 2, startButton.GetCurrentButtonSprite().getTexture()->getSize().y / 2);
	quitButton.GetCurrentButtonSprite().setOrigin(quitButton.GetCurrentButtonSprite().getTexture()->getSize().x / 2, quitButton.GetCurrentButtonSprite().getTexture()->getSize().y / 2);

	startButton.GetCurrentButtonSprite().setPosition(Window::GetInstance()->GetWindowSize().x / 2, Window::GetInstance()->GetWindowSize().y / 6 * 3);
	quitButton.GetCurrentButtonSprite().setPosition(startButton.GetCurrentButtonSprite().getPosition().x, startButton.GetCurrentButtonSprite().getPosition().y + startButton.GetCurrentButtonSprite().getTexture()->getSize().y + 20);
}

//Override Update method from base Component class
void MenuScene::Update(float deltaTime) {
	Scene::Update(deltaTime);

	//If start button is clicked load new scene
	if (startButton.IsClicked()) {
		SceneManager::LoadScene(1);
	}
	//If Quit button is clicked quit the game
	if (quitButton.IsClicked()) {
		Window::GetInstance()->IsClosed = true;
	}
}
