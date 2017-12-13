#include "LevelSelectScene.h"
#include "Window.h"
#include "SceneManager.h"

//Constructor
LevelSelectScene::LevelSelectScene(std::string sceneName) : Scene(sceneName) {

}

//Destructor
LevelSelectScene::~LevelSelectScene() {

}

//Override Awake method from base Component class
void LevelSelectScene::Awake() {
	Scene::Awake();

	//Setting drawing layers index
	GOUIBackgroundBars.SetDrawIndex(2);
	GOUIManager.SetDrawIndex(1);

	//Adding components to Background bars GameObject
	GOUIBackgroundBars.AddComponent(&backgroundBarTop);
	GOUIBackgroundBars.AddComponent(&backgroundBarBottom);

	//Set default values for background bars
	backgroundBarTop.setScale(0.5155f, 0.5155f);
	backgroundBarBottom.setScale(0.7f, 0.7f);
	backgroundBarBottom.setPosition(-10, Window::GetInstance()->GetWindowSize().y - (backgroundBarBottom.getTexture()->getSize().y / 2 + 10));

	//Set default values for back button
	buttonBack.GetCurrentButtonSprite().setScale(0.6f, 0.6f);
	buttonBack.GetCurrentButtonSprite().setPosition(4, Window::GetInstance()->GetWindowSize().y - 68);

	//Set default values for levelSelectText
	levelSelectText.setScale(0.4f, 0.4f);
	levelSelectText.setOrigin(levelSelectText.getTexture()->getSize().x / 2, levelSelectText.getTexture()->getSize().y / 2);
	levelSelectText.setPosition(Window::GetInstance()->GetWindowSize().x / 2, 33);

	//Adding components to UIManager GameObject
	GOUIManager.AddComponent(&levelSelectText);
	GOUIManager.AddComponent(&levelSelectManager);
	GOUIManager.AddComponent(&buttonBack);

}

//Override Start method from base Component class
void LevelSelectScene::Start(){
	Scene::Start();
}

//Override Update method from base Component class
void LevelSelectScene::Update(float deltaTime) {
	Scene::Update(deltaTime);
	
	//If any level button is clicked
	//load new scene
	if (levelSelectManager.HasSelectedLevel()) {
		std::cout << levelSelectManager.GetCurrentSelectedLevel() << std::endl;
		SceneManager::LoadScene(2);
	}
	
	//Back button
	if (buttonBack.IsClicked()) {
		SceneManager::LoadScene(0);
	}
}
