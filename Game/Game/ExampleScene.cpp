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
	/*
	//Enemy adding components
	enemyGameObject.AddComponent(&trump);
	enemyGameObject.AddComponent(&boxColliderTrump);

	enemyGameObject.AddComponent(&animator);
	enemyGameObject.AddComponent(&forwardWalkAnim);

	//Hero adding componets
	heroGameObject.AddComponent(&hero);
	heroGameObject.AddComponent(&boxColliderHero);
	
	//UIManager adding components
	*/

	testObject.AddComponent(&prisma);
}

void ExampleScene::Start() {
	Scene::Start();

	prisma.setScale(0.5f, 0.5f);
	prisma.setPosition(175, 500);
	prisma.setOrigin(prisma.getTexture()->getSize().x / 2, prisma.getTexture()->getSize().y / 2);

	prisma.setColor(sf::Color::Red);

	/*
	animator.PlayAnimation("backWalk");
	trump.setPosition(100, 10);

	hero.setScale(0.1f, 0.1f);
	hero.setPosition(200, 600);
	*/
}

void ExampleScene::Update(float deltaTime) {
	Scene::Update(deltaTime);

	if (Input::GetKeyDown(sf::Keyboard::A)) {
		prisma.setRotation(prisma.getRotation() - 50 * deltaTime);
	}
	if (Input::GetKeyDown(sf::Keyboard::D)) {
		prisma.setRotation(prisma.getRotation() + 50 * deltaTime);
		
		if (prisma.getColor().r == 255 && prisma.getColor().g == 0) {
			std::cout << "1" << std::endl;
			prisma.setColor(sf::Color(prisma.getColor().r, prisma.getColor().g, prisma.getColor().b + 10));
		}
		else if (prisma.getColor().g == 0 && prisma.getColor().b == 255) {
			std::cout << "2" << std::endl;
			prisma.setColor(sf::Color(prisma.getColor().r - 10, prisma.getColor().g, prisma.getColor().b));
		}
	}
}
