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

	std::cout << "Example scene 1 awake function runnning" << std::endl;

	gameObject1.AddComponent(&trump);
	gameObject1.AddComponent(&hero);

	gameObject1.AddComponent(&animator);

	gameObject1.AddComponent(&forwardWalkAnim);
	gameObject1.AddComponent(&backWalkAnim);
	gameObject1.AddComponent(&rightWalkAnim);
	gameObject1.AddComponent(&leftWalkAnim);


}

void ExampleScene::Start() {
	Scene::Start();
	std::cout << "Example scene 1 start function runnning" << std::endl;

	animator.PlayAnimation("backWalk");
	trump.SetPosition(100, 0);

	hero.SsetScale(0.1f, 0.1f);
	hero.SetPosition(100, 600);
}

void ExampleScene::Update(float deltaTime) {
	Scene::Update(deltaTime);
}
