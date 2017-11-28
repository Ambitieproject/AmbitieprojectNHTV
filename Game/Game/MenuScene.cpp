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

//Override Start method from base Component class
void MenuScene::Start() {
	Scene::Start();

	std::cout << "Menu Scene start function runnning" << std::endl;

	//Adding components to the UIManager GameObject
	GOUIManager.AddComponent(&startButton);
	GOUIManager.AddComponent(&quitButton);

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
