#include "ExampleScene.h"
#include "SceneManager.h"
#include "Input.h"
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
}

void ExampleScene::Start() {
	Scene::Start();
}

void ExampleScene::Update(float deltaTime) {
	Scene::Update(deltaTime);
}
