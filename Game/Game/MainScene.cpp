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


void MainScene::Setup() {
	Scene::Setup();

	//Setting draw indexes of GameObjects
	GOUIManager.SetDrawIndex(1);
	GOUIBackgroundBars.SetDrawIndex(2);
	GOPrisma.SetDrawIndex(2);
	GOColorManager.SetDrawIndex(2);

	//Adding components to ColorManager GameObject
	GOColorManager.AddComponent(&colorManager);

	//Adding components to Prisma GameObject
	GOPrisma.AddComponent(&prismaSprite);
	GOPrisma.AddComponent(&prisma);

	//Adding components to ReflectorBeamManager GameObject
	GOReflectorBeamManager.AddComponent(&reflectorBeam);

	//Adding components to MirrorManager GameObject
	GOMirrorManager.AddComponent(&mirrorManager);

	//Adding components to UIManager GameObject
	GOUIManager.AddComponent(&timeBackgroundSprite);
	GOUIManager.AddComponent(&timeText);
	GOUIManager.AddComponent(&timeManager);

	GOUIManager.AddComponent(&scoreText);
	GOUIManager.AddComponent(&scoreTextStatic);
	GOUIManager.AddComponent(&scoreManager);

	GOUIManager.AddComponent(&addMirrorButton);

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

	//Setting standard values for the scoreText
	scoreText.setString("23");
	scoreText.setScale(1, 1);
	scoreText.setPosition(10, 2);
	scoreText.setColor(sf::Color::Black);

	//Setting standard values for the scoreTextStatic
	scoreTextStatic.setString("points");
	scoreTextStatic.setScale(0.7, 0.7);
	scoreTextStatic.setPosition(10, 32);
	scoreTextStatic.setColor(sf::Color::Black);

	//Setting standard values of the addMirrorButton
	addMirrorButton.GetCurrentButtonSprite().setScale(0.5f, 0.5f);
	addMirrorButton.GetCurrentButtonSprite().setPosition(Window::GetInstance()->GetWindowSize().x - 80, 7);
}

void MainScene::Start() {
	Scene::Start();
}

void MainScene::Update(float deltaTime) {
	Scene::Update(deltaTime); 

	if (addMirrorButton.IsClicked()) {
		bool isNotInWay = false;

		for (auto it = mirrorManager.GetMirrors().begin(); it != mirrorManager.GetMirrors().end(); it++) {

			sf::Vector2f mirrorPos = it->second->GetComponent<BC::Sprite>()->getPosition();
			float width = it->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getGlobalBounds().width;
			float height = it->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getGlobalBounds().height;	
		}

		if (!isNotInWay) {
			mirrorManager.AddMirror();
		}
	}

	if (Input::GetKeyReleased(sf::Keyboard::Escape)) {
		SceneManager::LoadScene(0);
	}
}
