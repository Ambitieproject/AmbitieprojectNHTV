#include "PrismaMovementController.h"
#include "Window.h"



PrismaMovementController::PrismaMovementController(BC::Sprite* prismaSprite) : prisma(prismaSprite) {
	
}


PrismaMovementController::~PrismaMovementController() {

}

void PrismaMovementController::Start() {
	prisma->setScale(0.5f, 0.5f);
	prisma->setPosition(Window::GetInstance()->GetWindowSize().x / 2, Window::GetInstance()->GetWindowSize().y / 4 * 3);
	prisma->setOrigin(prisma->getTexture()->getSize().x / 2 - 10, prisma->getTexture()->getSize().y / 2);

	rotateSpeed = 80;
}

void PrismaMovementController::Update(float deltaTime) {
	if (Input::GetKeyDown(sf::Keyboard::A)) {
		prisma->setRotation(prisma->getRotation() - rotateSpeed * deltaTime);
	}
	if (Input::GetKeyDown(sf::Keyboard::D)) {
		prisma->setRotation(prisma->getRotation() + rotateSpeed * deltaTime);
	}
}
