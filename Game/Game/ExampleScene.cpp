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

	//Enemy adding components
	enemyGameObject.AddComponent(&trump);
	enemyGameObject.AddComponent(&boxColliderTrump);

	enemyGameObject.AddComponent(&animator);
	enemyGameObject.AddComponent(&forwardWalkAnim);

	//Hero adding componets
	heroGameObject.AddComponent(&hero);
	heroGameObject.AddComponent(&boxColliderHero);

	//UIManager adding components

}

void ExampleScene::Start() {
	Scene::Start();
	std::cout << "Example scene 1 start function runnning" << std::endl;

	animator.PlayAnimation("backWalk");
	trump.setPosition(100, 10);

	hero.setScale(0.1f, 0.1f);
	hero.setPosition(200, 600);
}

void ExampleScene::Update(float deltaTime) {
	Scene::Update(deltaTime);

	if (Input::GetKeyDown(sf::Keyboard::A)) {
		hero.move(-1, 0);
	}
	if (Input::GetKeyDown(sf::Keyboard::D)) {
		hero.move(1, 0);
	}
	if (Input::GetKeyDown(sf::Keyboard::W)) {
		hero.move(0, -1);
	}
	if (Input::GetKeyDown(sf::Keyboard::S)) {
		hero.move(0, 1);
	}
}
