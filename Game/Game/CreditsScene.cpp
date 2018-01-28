#include "CreditsScene.h"
#include "SceneManager.h"
#include "Window.h"

//Constructor
CreditsScene::CreditsScene(std::string sceneName) : Scene(sceneName) {

}

//Destructor
CreditsScene::~CreditsScene() {

}

//Override Setup method from base Scene class
void CreditsScene::Setup() {
	Scene::Setup();

	//Setting drawing layers for GameObjects
	GOcreditManager.SetDrawIndex(0);

	//Add components to CreditManager GameObject
	GOcreditManager.AddComponent(&CreditSprite);

	//Setting default values for credit sprite
	CreditSprite.setScale(0.5, 0.5f);
	CreditSprite.setOrigin(CreditSprite.getTexture()->getSize().x * 0.5f, 0);
	CreditSprite.setPosition(Window::GetWindowSize().x * 0.5f, Window::GetWindowSize().y);

}

//Override Start method from base Scene class
void CreditsScene::Start() {
	Scene::Start();

	//Set background render color
	Window::SetWindowRenderColor(sf::Color(11, 3, 44));
}

//Override Update method from base Scene class
void CreditsScene::Update(float deltaTime) {
	Scene::Update(deltaTime);

	//Move creditSprite up
	CreditSprite.move(0, -50 * deltaTime);

	//Load scene if creditSprite is out of the screen
	if (CreditSprite.getPosition().y <= -860) {
		SceneManager::LoadScene(1);
	}
	//Load scene if any key is down
	if (Input::GetAnyKeyDown()) {
		SceneManager::LoadScene(1);
	}
}
