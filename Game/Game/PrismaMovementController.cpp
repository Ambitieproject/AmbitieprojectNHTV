#include "PrismaMovementController.h"
#include "Window.h"
#include "SceneManager.h"



PrismaMovementController::PrismaMovementController(BC::Sprite* prismaSprite) : prisma(prismaSprite) {
	
}


PrismaMovementController::~PrismaMovementController() {

}

void PrismaMovementController::Start() {
	Component::Start();

	colorManager = SceneManager::GetActiveScene().FindGameObjectByName("ColorManager")->GetComponent<ColorManager>();

	//Setting default values of prism
	prisma->setScale(0.25f, 0.25f);
	prisma->setPosition(Window::GetInstance()->GetWindowSize().x / 2, Window::GetInstance()->GetWindowSize().y / 4 * 3);
	prisma->setOrigin(prisma->getTexture()->getSize().x * 0.5f, (prisma->getTexture()->getSize().y * 0.5f) + 40);

	rotateSpeed = 80;

	//Setting first pixel
	currentPrismaColorIndex = 0;
	currentPrismaColor = colorManager->GetColors()[currentPrismaColorIndex];
}

void PrismaMovementController::Update(float deltaTime) {
	Component::Update(deltaTime);

	if (Input::GetKeyDown(sf::Keyboard::A)) {
		prisma->setRotation(prisma->getRotation() - rotateSpeed * deltaTime);
		isMovingLeft = true;

		if (currentPrismaColorIndex >= colorManager->GetColors().size() - 1) {
			currentPrismaColorIndex = 0;
		}

		currentPrismaColorIndex++;
		currentPrismaColor = colorManager->GetColors()[currentPrismaColorIndex];
	}
	else if (Input::GetKeyDown(sf::Keyboard::D)) {
		prisma->setRotation(prisma->getRotation() + rotateSpeed * deltaTime);
		isMovingRight = true;

		if (currentPrismaColorIndex < 0 + 1) {
			currentPrismaColorIndex = colorManager->GetColors().size();
		}

		currentPrismaColorIndex--;
		currentPrismaColor = colorManager->GetColors()[currentPrismaColorIndex];
	}
	else {
		isMovingLeft = false;
		isMovingRight = false;
	}
	
}

bool PrismaMovementController::IsMovingLeft() {
	return isMovingLeft;
}

bool PrismaMovementController::IsMovingRight() {
	return isMovingRight;
}

//Gets the current prism color
sf::Color& PrismaMovementController::GetCurrentPrismColor() {
	return currentPrismaColor;
}
