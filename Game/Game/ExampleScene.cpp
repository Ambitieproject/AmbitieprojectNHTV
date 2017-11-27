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

	sf::Image colorValueImage;
	colorValueImage.loadFromFile("../Assets/colorScheme.png");

	for (int i = 0; i < colorValueImage.getSize().x; i++) {
		prismaColors.push_back(colorValueImage.getPixel(i, 0));
	}

	currentPrismaColorIndex = 0;
	currentPrismaColor = prismaColors[currentPrismaColorIndex];
	//prisma.setColor(currentPrismaColor);
}

void ExampleScene::Update(float deltaTime) {
	Scene::Update(deltaTime);

	if (Input::GetKeyDown(sf::Keyboard::A)) {
		//prisma.setRotation(prisma.getRotation() - 50 * deltaTime);

		if (currentPrismaColorIndex < 0 + 1) {
			currentPrismaColorIndex = prismaColors.size();
		}

		currentPrismaColorIndex--;
		currentPrismaColor = prismaColors[currentPrismaColorIndex];
		//prisma.setColor(currentPrismaColor);
	}
	if (Input::GetKeyDown(sf::Keyboard::D)) {
		//prisma.setRotation(prisma.getRotation() + 50 * deltaTime);

		if (currentPrismaColorIndex >= prismaColors.size() - 1) {
			currentPrismaColorIndex = 0;
		}

		currentPrismaColorIndex++;
		currentPrismaColor = prismaColors[currentPrismaColorIndex];
		//prisma.setColor(currentPrismaColor);
	}

	
	
}
