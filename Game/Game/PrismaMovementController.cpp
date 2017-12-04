#include "PrismaMovementController.h"
#include "Window.h"



PrismaMovementController::PrismaMovementController(BC::Sprite* prismaSprite) : prisma(prismaSprite) {
	
}


PrismaMovementController::~PrismaMovementController() {

}

void PrismaMovementController::Start() {
	prisma->setScale(0.25f, 0.25f);
	prisma->setPosition(Window::GetInstance()->GetWindowSize().x / 2, Window::GetInstance()->GetWindowSize().y / 4 * 3);
	prisma->setOrigin(prisma->getTexture()->getSize().x * 0.5f, (prisma->getTexture()->getSize().y * 0.5f) + 40);

	rotateSpeed = 80;
}

void PrismaMovementController::Update(float deltaTime) {
	if (Input::GetKeyDown(sf::Keyboard::A)) {
		prisma->setRotation(prisma->getRotation() - rotateSpeed * deltaTime);
		isMovingLeft = true;
	}
	else if (Input::GetKeyDown(sf::Keyboard::D)) {
		prisma->setRotation(prisma->getRotation() + rotateSpeed * deltaTime);
		isMovingRight = true;
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
