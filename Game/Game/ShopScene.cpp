#include "ShopScene.h"
#include "SceneManager.h"
#include "Window.h"

//Constructor
ShopScene::ShopScene(std::string sceneName) : Scene(sceneName) {

}

//Destructor
ShopScene::~ShopScene() {

}

//Override Setup method from base Component class
void ShopScene::Setup() {
	Scene::Setup();

	//Setting drawing layers index
	GOShopManager.SetDrawIndex(0);
	GOUIManager.SetDrawIndex(3);

	//Adding components to ShopManager GameObject
	GOShopManager.AddComponent(&shopManager);

	//Adding components to Background bars GameObject
	GOUIManager.AddComponent(&backgroundBarTop);
	GOUIManager.AddComponent(&backgroundItemHolder);
	GOUIManager.AddComponent(&backgroundBarBottom);

	//Adding components to UIManager GameObject
	GOUIManager.AddComponent(&shopTitleText);
	GOUIManager.AddComponent(&buttonBack);

	//Set default values for background bars
	backgroundBarTop.setScale(0.5155f, 0.5155f);
	backgroundBarBottom.setScale(0.7f, 0.7f);
	backgroundBarBottom.setPosition(-10, Window::GetInstance()->GetWindowSize().y - (backgroundBarBottom.getTexture()->getSize().y / 2 + 10));

	//Set default values for background item holder
	backgroundItemHolder.setScale(0.5155f, 0.5155f);
	backgroundItemHolder.setPosition(backgroundItemHolder.getPosition().x, 150);

	//Set default values for back button
	buttonBack.GetCurrentButtonSprite().setScale(0.6f, 0.6f);
	buttonBack.GetCurrentButtonSprite().setPosition(4, Window::GetInstance()->GetWindowSize().y - 68);

	//Set default values for levelSelectText
	shopTitleText.setScale(0.4f, 0.4f);
	shopTitleText.setOrigin(shopTitleText.getTexture()->getSize().x / 2, shopTitleText.getTexture()->getSize().y / 2);
	shopTitleText.setPosition(Window::GetInstance()->GetWindowSize().x / 2, 33);
}

//Override Start method from base Component class
void ShopScene::Start() {
	Scene::Start();
}

//Override Update method from base Component class
void ShopScene::Update(float deltaTime) {
	Scene::Update(deltaTime);

	//Load Menu if escape key is pressed
	if (Input::GetKeyDown(sf::Keyboard::Escape)) {
		SceneManager::LoadScene(0);
	}

	//Load Menu if back button is clicked
	if (buttonBack.IsClicked()) {
		SceneManager::LoadScene(0);
	}
}
