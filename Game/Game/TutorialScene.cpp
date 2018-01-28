#include "TutorialScene.h"
#include "SceneManager.h"

//Constructor
TutorialScene::TutorialScene(std::string sceneName) : Scene(sceneName) {

}

//Destructor
TutorialScene::~TutorialScene() {

}

//Override Setup method from base Scene class
void TutorialScene::Setup() {
	Scene::Setup();

	//Setting draw indexes
	GOBackgroundHolder.SetDrawIndex(0);

	//Add components to background holder GameObject
	GOBackgroundHolder.AddComponent(&backgroundSprite);
}

//Override Start method from base Scene class
void TutorialScene::Start() {
	Scene::Start();
}

//Override Update method from base Scene class
void TutorialScene::Update(float deltaTime) {
	Scene::Update(deltaTime);

	//If any key is pressed, load menu
	if (Input::GetAnyKeyPressed()) {
		SceneManager::LoadScene(1);
	}
}