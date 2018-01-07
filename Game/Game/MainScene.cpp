#include "MainScene.h"
#include "SceneManager.h"
#include "Input.h"
#include "Window.h"
#include "BaseComponents.hpp"

//Constructor
MainScene::MainScene(std::string sceneName) : Scene(sceneName) {

}

//Destructor
MainScene::~MainScene() {

}

//Override Setup method from base Scene class
void MainScene::Setup() {
	Scene::Setup();

	//Setting draw indexes of GameObjects
	GOUIManager.SetDrawIndex(1);
	GOValidationManager.SetDrawIndex(1);
	GOUIBackgroundBars.SetDrawIndex(2);
	GOPrisma.SetDrawIndex(2);

	//Adding components to ValidationManager GameObject
	GOValidationManager.AddComponent(&validationManager);

	//Adding components to Prisma GameObject
	GOPrisma.AddComponent(&prismaSprite);
	GOPrisma.AddComponent(&prismBoxCollider);

	//Adding components to ReflectorBeamManager GameObject
	GOReflectorBeamManager.AddComponent(&reflectorBeam);

	//Adding components to UIManager GameObject
	GOUIManager.AddComponent(&timeBackgroundSprite);
	GOUIManager.AddComponent(&timeText);
	GOUIManager.AddComponent(&addMirrorButton);

	//Adding components to GameManager GameObject
	GOGameManager.AddComponent(&gameFlowManager);
	GOGameManager.AddComponent(&scoreManager);
	GOGameManager.AddComponent(&timeManager);
	GOGameManager.AddComponent(&mirrorManager);
	GOGameManager.AddComponent(&levelLoader);

	//Setting default values of prism
	prismaSprite.setScale(0.25f, 0.25f);
	prismaSprite.setPosition(Window::GetInstance()->GetWindowSize().x / 2, Window::GetInstance()->GetWindowSize().y - 60);
	prismaSprite.setOrigin(prismaSprite.getTexture()->getSize().x * 0.5f, (prismaSprite.getTexture()->getSize().y * 0.5f) + 40);

	//Adding components to BackgroundBars GameObject
	GOUIBackgroundBars.AddComponent(&backgroundBarTop);

	backgroundBarTop.setScale(0.5155f, 0.5155f);

	timeBackgroundSprite.setOrigin(timeBackgroundSprite.getTexture()->getSize().x / 2, timeBackgroundSprite.getTexture()->getSize().y / 2);
	timeBackgroundSprite.setPosition(Window::GetInstance()->GetWindowSize().x / 2, 70);
	timeBackgroundSprite.setScale(0.5f, 0.5f);

	//Setting standard values for the timeText
	timeText.setString("02:00");
	timeText.setPosition(Window::GetInstance()->GetWindowSize().x / 2 - 36, 50);
	timeText.setColor(sf::Color::Black);

	//Setting standard values of the addMirrorButton
	addMirrorButton.GetCurrentButtonSprite().setScale(0.5f, 0.5f);
	addMirrorButton.GetCurrentButtonSprite().setPosition(Window::GetInstance()->GetWindowSize().x - 80, 7);
}

//Override Start method from base Scene class
void MainScene::Start() {
	Scene::Start();
}

//Override Update method from base Scene class
void MainScene::Update(float deltaTime) {
	Scene::Update(deltaTime); 

	//If escape key is pressed
	if (Input::GetKeyReleased(sf::Keyboard::Escape)) {
		SceneManager::LoadScene(0);
	}

	//If switching bool is true switch to other scene
	if (gameFlowManager.FromLevelToScene()) {
		SceneManager::LoadScene(0);
	}
}
