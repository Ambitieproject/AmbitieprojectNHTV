#include "ShopScene.h"
#include "SceneManager.h"
#include "Window.h"

//Constructor
ShopScene::ShopScene(std::string sceneName) : Scene(sceneName) {

}

//Destructor
ShopScene::~ShopScene() {

}

//Override Setup method from base Scene class
void ShopScene::Setup() {
	Scene::Setup();

	//Setting drawing layers index
	GOShopManager.SetDrawIndex(0);
	GOUIManager.SetDrawIndex(3);

	//Adding components to ShopManager GameObject
	GOShopManager.AddComponent(&shopManager);

	//Adding components to Background bars GameObject
	GOUIManager.AddComponent(&backgroundBarTitle);
	GOUIManager.AddComponent(&backgroundItemHolder);
	GOUIManager.AddComponent(&backgroundCurrencyHolder);

	//Adding components to UIManager GameObject
	GOUIManager.AddComponent(&buttonBack);

	//Set default values the title background bar
	backgroundBarTitle.setScale(1, 1);
	backgroundBarTitle.setPosition(15, 20);

	//Set default values for background item holder
	backgroundItemHolder.setScale(0.49f, 0.49f);
	backgroundItemHolder.setPosition(12, 190);

	//Set default values for currency background holder
	backgroundCurrencyHolder.setScale(0.5155f, 0.5155f);
	backgroundCurrencyHolder.setPosition(300, 128);

	//Set default values for back button
	buttonBack.GetCurrentButtonSprite().setScale(0.7f, 0.7f);
	buttonBack.GetCurrentButtonSprite().setPosition(15, Window::GetWindowSize().y - 70);
}

//Override Start method from base Scene class
void ShopScene::Start() {
	Scene::Start();

	//Set background render color
	Window::SetWindowRenderColor(sf::Color(238, 24, 78));
}

//Override Update method from base Scene class
void ShopScene::Update(float deltaTime) {
	Scene::Update(deltaTime);

	//Load Menu if back button is clicked
	if (buttonBack.IsClicked()) {
		//Play click sound
		AudioManager::GetSound("ButtonClickBackSound")->play();
		//Load scene
		SceneManager::LoadScene(1);
	}
}
