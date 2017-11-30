#include "ReflectorBeamManager.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Window.h"



ReflectorBeamManager::ReflectorBeamManager(std::string beamFilePath) : beamFilePath(beamFilePath) {
	beamIndex = 0;
}


ReflectorBeamManager::~ReflectorBeamManager() {

}

void ReflectorBeamManager::Start() {
	//Setting references
	prisma = SceneManager::GetActiveScene().FindGameObjectByName("Prisma")->GetComponent<BC::Sprite>();
	prismaMovementController = SceneManager::GetActiveScene().FindGameObjectByName("Prisma")->GetComponent<PrismaMovementController>();
	mirrorManager = SceneManager::GetActiveScene().FindGameObjectByName("MirrorManager")->GetComponent<MirrorManager>();

	sf::Image colorValueImage;
	colorValueImage.loadFromFile("../Assets/colorScheme.png");

	for (int i = 0; i < colorValueImage.getSize().x; i++) {
		prismaColors.push_back(colorValueImage.getPixel(i, 0));
	}

	currentPrismaColorIndex = 0;
	currentPrismaColor = prismaColors[currentPrismaColorIndex];

	AddBeam(sf::Vector2f(prisma->getPosition().x, prisma->getPosition().y - 70), 0);
}

void ReflectorBeamManager::Update(float deltaTime) {
	Component::Update(deltaTime);

	SetBeamColor();

	//for every beam
	for (auto it = beams.begin(); it != beams.end(); it++) {
		//Put pointer in temperary storage
		ReflectorBeam* reflectorBeam = it->second;

		reflectorBeam->Update(deltaTime);
	}
}

//Adds a beam with a position and rotation
void ReflectorBeamManager::AddBeam(sf::Vector2f position, float rotateAngel) {
	//Make new beam instance pointer
	ReflectorBeam* beam = new ReflectorBeam(mirrorManager);

	//Add components from the beam to the GameObject
	gameObject->AddComponent(&beam->GetSprite());
	gameObject->AddComponent(&beam->GetBoxCollider());

	//Set beam position and rotation
	beam->GetSprite().setPosition(position);
	beam->GetSprite().rotate(rotateAngel);

	//Insert beam into beam map and increase beamIndex
	beams.insert(std::pair<int, ReflectorBeam*>(beamIndex, beam));
	beamIndex++;
}

//Sets the colors of every beam
void ReflectorBeamManager::SetBeamColor() {
	if (prismaMovementController->IsMovingRight()) {
		if (currentPrismaColorIndex >= prismaColors.size() - 1) {
			currentPrismaColorIndex = 0;
		}

		currentPrismaColorIndex++;
		currentPrismaColor = prismaColors[currentPrismaColorIndex];

		for (auto it = beams.begin(); it != beams.end(); it++) {
			it->second->GetSprite().setColor(currentPrismaColor);
		}
	}
	if (prismaMovementController->IsMovingLeft()) {
		if (currentPrismaColorIndex < 0 + 1) {
			currentPrismaColorIndex = prismaColors.size();
		}

		currentPrismaColorIndex--;
		currentPrismaColor = prismaColors[currentPrismaColorIndex];

		for (auto it = beams.begin(); it != beams.end(); it++) {
			it->second->GetSprite().setColor(currentPrismaColor);
		}
	}
}

void ReflectorBeamManager::CalculateNewBeam(ReflectorBeam* previousBeam, GameObject* reflectingMirror) {
	BC::Sprite* mirrorSprite = gameObject->GetComponent<BC::Sprite>();

	AddBeam(mirrorSprite->getPosition(), mirrorSprite->getRotation());
}
