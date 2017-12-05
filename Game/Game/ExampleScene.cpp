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

	GOPrisma.AddComponent(&prismaSprite);
	GOPrisma.AddComponent(&prisma);

	GOReflectorBeamManager.AddComponent(&reflectorBeam);

	GOMirrorManager.AddComponent(&mirrorManager);

	GOUIBackgroundBars.AddComponent(&backgroundBarTop);
	GOUIBackgroundBars.AddComponent(&backgroundBarBottom);

	float size = 0.5155f;

	backgroundBarTop.setScale(size, size);
	backgroundBarBottom.setScale(size, size);
	backgroundBarBottom.setPosition(0, Window::GetInstance()->GetWindowSize().y - backgroundBarBottom.getScale().y * backgroundBarBottom.getTexture()->getSize().y);
}

void ExampleScene::Start() {
	Scene::Start();
}

void ExampleScene::Update(float deltaTime) {
	Scene::Update(deltaTime);
}
