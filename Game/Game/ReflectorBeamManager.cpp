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
	colorManager = SceneManager::GetActiveScene().FindGameObjectByName("ColorManager")->GetComponent<ColorManager>();

	//Add first beam
	AddBeam(sf::Vector2f(prisma->getPosition().x, prisma->getPosition().y - 100), 30);
	std::cout << "reflector beam start" << std::endl;
	for (auto it = beams.begin(); it != beams.end(); it++) {
		it->second->GetComponent<ReflectorBeam>()->SetLineColor(prismaMovementController->GetCurrentPrismColor());
	}
}

void ReflectorBeamManager::Update(float deltaTime) {
	Component::Update(deltaTime);

	if (prismaMovementController->IsMovingRight() || prismaMovementController->IsMovingLeft()) {
		for (auto it = beams.begin(); it != beams.end(); it++) {
			it->second->GetComponent<ReflectorBeam>()->SetLineColor(prismaMovementController->GetCurrentPrismColor());
		}
	}
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
