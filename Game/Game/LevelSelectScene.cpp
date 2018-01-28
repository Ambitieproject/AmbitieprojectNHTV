#include "LevelSelectScene.h"
#include "Window.h"
#include "SceneManager.h"

//Constructor
LevelSelectScene::LevelSelectScene(std::string sceneName) : Scene(sceneName) {

}

//Destructor
LevelSelectScene::~LevelSelectScene() {

}

//Override Setup method from base Scene class
void LevelSelectScene::Setup() {
	Scene::Setup();

	//Setting drawing layers index
	GOUIBackgroundBars.SetDrawIndex(2);
	GOUIManager.SetDrawIndex(1);

	//Adding components to Background bars GameObject
	GOUIBackgroundBars.AddComponent(&backgroundBarTitle);

	//Adding components to UIManager GameObject
	GOUIManager.AddComponent(&levelSelectManager);
	GOUIManager.AddComponent(&buttonBack);

	//Set default values for background bars
	backgroundBarTitle.setScale(1, 1);
	backgroundBarTitle.setPosition(15, 20);

	//Set default values for back button
	buttonBack.GetCurrentButtonSprite().setScale(0.7f, 0.7f);
	buttonBack.GetCurrentButtonSprite().setPosition(15, Window::GetWindowSize().y - 70);
}

//Override Start method from base Scene class
void LevelSelectScene::Start(){
	Scene::Start();

	//Set background render color
	Window::SetWindowRenderColor(sf::Color(104, 9, 251));
}

//Override Update method from base Scene class
void LevelSelectScene::Update(float deltaTime) {
	Scene::Update(deltaTime);
	
	//If any level button is clicked
	//load new scene
	if (levelSelectManager.HasSelectedLevel()) {

		//Play click sound
		AudioManager::GetSound("ButtonClickForwardSound")->play();

		//Save JSON
		json j;
		j["CurrentLevel"] = levelSelectManager.GetCurrentSelectedLevel();
		FileReadWrite::WriteJSONToFile("../Assets/JSON/CurrentLevel.json", j);
		SceneManager::LoadScene(3);
	}
	
	//Back button
	if (buttonBack.IsClicked()) {
		//Play click sound
		AudioManager::GetSound("ButtonClickBackSound")->play();
		//Load scene
		SceneManager::LoadScene(1);
	}
}
