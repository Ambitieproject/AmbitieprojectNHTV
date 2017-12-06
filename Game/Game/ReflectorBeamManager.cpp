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

	AddBeam(sf::Vector2f(prisma->getPosition().x, prisma->getPosition().y - 100), 30);

	for (int i = 0; i < colorValueImage.getSize().x; i++) {
		prismaColors.push_back(colorValueImage.getPixel(i, 0));
	}

	currentPrismaColorIndex = 0;
	currentPrismaColor = prismaColors[currentPrismaColorIndex];

	for (auto it = beams.begin(); it != beams.end(); it++) {
		it->second->GetComponent<ReflectorBeam>()->SetLineColor(currentPrismaColor);
	}
}

void ReflectorBeamManager::Update(float deltaTime) {
	Component::Update(deltaTime);

	SetBeamColor();
}

//Adds a beam with a position and rotation
GameObject& ReflectorBeamManager::AddBeam(sf::Vector2f position, float rotateAngel) {
	//Make new GameObject instance pointer
	GameObject* beam = new GameObject("Beam", gameObject->GetScene());

	//Set draw index of GameObject
	beam->SetDrawIndex(3);

	//Make new beam instance pointer
	ReflectorBeam* reflectorBeamComponent = new ReflectorBeam(mirrorManager, this);

	//Add components from the beam to the GameObject
	beam->AddComponent(reflectorBeamComponent);

	reflectorBeamComponent->GetLine()[0].position = position;

	//Insert beam into beam map and increase beamIndex
	beams.insert(std::pair<int, GameObject*>(beamIndex, beam));
	beamIndex++;

	return *beam;
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
			it->second->GetComponent<ReflectorBeam>()->SetLineColor(currentPrismaColor);
		}
	}
	if (prismaMovementController->IsMovingLeft()) {
		if (currentPrismaColorIndex < 0 + 1) {
			currentPrismaColorIndex = prismaColors.size();
		}

		currentPrismaColorIndex--;
		currentPrismaColor = prismaColors[currentPrismaColorIndex];

		for (auto it = beams.begin(); it != beams.end(); it++) {
			it->second->GetComponent<ReflectorBeam>()->SetLineColor(currentPrismaColor);
		}
	}
}
