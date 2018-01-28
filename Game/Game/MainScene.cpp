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
	GOPrism.SetDrawIndex(2);

	//Adding components to ValidationManager GameObject
	GOValidationManager.AddComponent(&validationManager);

	//Adding components to Prisma GameObject
	GOPrism.AddComponent(&prismSprite);
	GOPrism.AddComponent(&prismBoxCollider);

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

	//Setting default values for prism sprite
	prismSprite.setScale(0.6f, 0.6f);
	prismSprite.setPosition(Window::GetWindowSize().x / 2, Window::GetWindowSize().y - 60);
	prismSprite.setOrigin(prismSprite.getTexture()->getSize().x * 0.5f, (prismSprite.getTexture()->getSize().y * 0.5f) + 40);
	prismSprite.setColor(sf::Color(prismSprite.getColor().r, prismSprite.getColor().g, prismSprite.getColor().b, 230));

	//Adding components to BackgroundBars GameObject
	GOUIBackgroundBars.AddComponent(&backgroundBarTop);

	//Set default values for background bar top
	backgroundBarTop.setScale(1.2f, 1);
	backgroundBarTop.setPosition(-5, -5);

	//Set default values for background time sprite
	timeBackgroundSprite.setOrigin(timeBackgroundSprite.getTexture()->getSize().x / 2, timeBackgroundSprite.getTexture()->getSize().y / 2);
	timeBackgroundSprite.setPosition(Window::GetWindowSize().x / 2, 100);
	timeBackgroundSprite.setScale(0.8f, 0.8f);

	//Setting standard values for the timeText
	timeText.setString("00:00");
	timeText.setPosition(Window::GetWindowSize().x / 2 - 40, 78);
	timeText.setColor(sf::Color::White);
	timeText.setStyle(sf::Text::Bold);

	//Setting standard values of the addMirrorButton
	addMirrorButton.GetCurrentButtonSprite().setScale(1, 1);
	addMirrorButton.GetCurrentButtonSprite().setPosition(Window::GetWindowSize().x - 80, 17);
}

//Override Start method from base Scene class
void MainScene::Start() {
	Scene::Start();

	//Set background render color
	Window::SetWindowRenderColor(sf::Color(193, 193, 193));
}

//Override Update method from base Scene class
void MainScene::Update(float deltaTime) {
	Scene::Update(deltaTime); 

	//If escape key is pressed
	if (Input::GetKeyReleased(sf::Keyboard::Escape)) {
		SceneManager::LoadScene(1);
	}

	//If switching bool is true switch to other scene
	if (gameFlowManager.FromLevelToMenu()) {
		SceneManager::LoadScene(1);
	}
}
