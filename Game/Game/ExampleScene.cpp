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

	gameObject1.AddComponent(&sprite);
	gameObject1.AddComponent(&animator);

	gameObject1.AddComponent(&forwardWalkAnim);
	gameObject1.AddComponent(&backWalkAnim);
	gameObject1.AddComponent(&rightWalkAnim);
	gameObject1.AddComponent(&leftWalkAnim);
}

void ExampleScene::Start() {
	Scene::Start();

	std::cout << "Example scene 1 start function runnning" << std::endl;
}

void ExampleScene::Update(float deltaTime) {
	Scene::Update(deltaTime);

	if (Input::GetKeyPressed(sf::Keyboard::W)) {
		gameObject1.GetComponent<BC::Animator>()->PlayAnimation("forwardWalk");
	}
	if (Input::GetKeyPressed(sf::Keyboard::S)) {
		gameObject1.GetComponent<BC::Animator>()->PlayAnimation("backWalk");
	}
	if (Input::GetKeyPressed(sf::Keyboard::D)) {
		gameObject1.GetComponent<BC::Animator>()->PlayAnimation("rightWalk");
	}
	if (Input::GetKeyPressed(sf::Keyboard::A)) {
		gameObject1.GetComponent<BC::Animator>()->PlayAnimation("leftWalk");
	}
}
