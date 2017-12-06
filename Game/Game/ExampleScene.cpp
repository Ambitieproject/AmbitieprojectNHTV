#include "ExampleScene.h"
#include "SceneManager.h"
#include "Input.h"
#include "Window.h"
#include "BaseComponents.hpp"

ExampleScene::ExampleScene(std::string sceneName) : Scene(sceneName) {

}


ExampleScene::~ExampleScene() {

}


void ExampleScene::Awake() {
	Scene::Awake();

	//Setting draw indexes of GameObjects
	GOTimeManager.SetDrawIndex(1);
	GOUIBackgroundBars.SetDrawIndex(2);
	GOPrisma.SetDrawIndex(2);

	//Adding components to Prisma GameObject
	GOPrisma.AddComponent(&prismaSprite);
	GOPrisma.AddComponent(&prisma);

	//Adding components to ReflectorBeamManager GameObject
	GOReflectorBeamManager.AddComponent(&reflectorBeam);

	//Adding components to MirrorManager GameObject
	GOMirrorManager.AddComponent(&mirrorManager);

	//Adding components to TimeManager GameObject
	GOTimeManager.AddComponent(&timeBackgroundSprite);
	GOTimeManager.AddComponent(&timeText);
	GOTimeManager.AddComponent(&timeManager);

	//Adding components to BackgroundBars GameObject
	GOUIBackgroundBars.AddComponent(&backgroundBarTop);
	GOUIBackgroundBars.AddComponent(&backgroundBarBottom);

	float size = 0.5155f;

	backgroundBarTop.setScale(size, size);
	backgroundBarBottom.setScale(size, size);
	backgroundBarBottom.setPosition(0, Window::GetInstance()->GetWindowSize().y - backgroundBarBottom.getScale().y * backgroundBarBottom.getTexture()->getSize().y);

	timeBackgroundSprite.setOrigin(timeBackgroundSprite.getTexture()->getSize().x / 2, timeBackgroundSprite.getTexture()->getSize().y / 2);
	timeBackgroundSprite.setPosition(Window::GetInstance()->GetWindowSize().x / 2, 70);
	timeBackgroundSprite.setScale(0.5f, 0.5f);

	timeText.setString("02:00");
	timeText.setScale(0.55f, 0.55f);
	timeText.setPosition(Window::GetInstance()->GetWindowSize().x / 2 - 43, 60);
	timeText.setColor(sf::Color::Black);
}

void ExampleScene::Start() {
	Scene::Start();
}

void ExampleScene::Update(float deltaTime) {
	Scene::Update(deltaTime);
}
