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

	trumpObject.AddComponent(&trump);
	trumpObject.AddComponent(&boxColliderTrump);

	trump2Object.AddComponent(&animator);

	trump2Object.AddComponent(&forwardWalkAnim);
	trump2Object.AddComponent(&backWalkAnim);
	trump2Object.AddComponent(&rightWalkAnim);
	trump2Object.AddComponent(&leftWalkAnim);

	trump2Object.AddComponent(&trump2);
	trump2Object.AddComponent(&boxColliderTrump2);

	heroObject.AddComponent(&hero);
	heroObject.AddComponent(&boxColliderHero);
}

void ExampleScene::Start() {
	Scene::Start();
	std::cout << "Example scene 1 start function runnning" << std::endl;

	animator.PlayAnimation("backWalk");
	trump.setPosition(100, 10);

	trump2.setScale(0.1f, 0.1f);
	trump2.setPosition(280, 10);

	hero.setScale(0.1f, 0.1f);
	hero.setPosition(100, 300);

}

void ExampleScene::Update(float deltaTime) {
	Scene::Update(deltaTime);

	BC::Collider* colBegin = boxColliderHero.OnBeginOverlap();
	BC::Collider* colStay = boxColliderHero.OnStayOverlap();
	BC::Collider* colEnd = boxColliderHero.OnEndOverlap();

	if (colBegin) {
		std::cout << "Begin " << colBegin->GameObject->Name << std::endl;
		GameObject gameOBJ = GameObject("BOEM", *this);
		DestroyComponent(colBegin);
	}
	if (colStay) {
		//std::cout << "Stay" << std::endl;
	}
	if (colEnd) {
		std::cout << "End " << colEnd->GameObject->Name << std::endl;
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
