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
	gameObject1.AddComponent(&boxColliderTrump);

	gameObject1.AddComponent(&trump2);
	gameObject1.AddComponent(&boxColliderTrump2);

	gameObject1.AddComponent(&hero);
	gameObject1.AddComponent(&boxColliderHero);

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
	trump.setPosition(100, 10);

	trump2.setScale(0.1f, 0.1f);
	trump2.setPosition(200, 10);

	hero.setScale(0.1f, 0.1f);
	hero.setPosition(100, 300);
}

void ExampleScene::Update(float deltaTime) {
	Scene::Update(deltaTime);

	if (boxColliderHero.OnBeginOverlap()) {
		std::cout << "Begin" << std::endl;
	}
	if (boxColliderHero.OnStayOverlap()) {
		std::cout << "Stay" << std::endl;
	}
	if (boxColliderHero.OnEndOverlap()) {
		std::cout << "End" << std::endl;
	}

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
