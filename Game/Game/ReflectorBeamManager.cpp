#include "ReflectorBeamManager.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Window.h"

//Constructor
ReflectorBeamManager::ReflectorBeamManager(std::string beamFilePath) : beamFilePath(beamFilePath) {
	
}

//Destructor
ReflectorBeamManager::~ReflectorBeamManager() {

}

//Override Start method from base Component class
void ReflectorBeamManager::Start() {
	//Setting references
	prisma = SceneManager::GetActiveScene().FindGameObjectByName("Prisma")->GetComponent<BC::Sprite>();
	prismaMovementController = SceneManager::GetActiveScene().FindGameObjectByName("Prisma")->GetComponent<PrismaMovementController>();
	mirrorManager = SceneManager::GetActiveScene().FindGameObjectByName("MirrorManager")->GetComponent<MirrorManager>();
	colorManager = SceneManager::GetActiveScene().FindGameObjectByName("ColorManager")->GetComponent<ColorManager>();

	//Set begin values
	beamIndex = 0;

	sf::Vector2f beamPos = sf::Vector2f(Window::GetInstance()->GetWindowSize().x / 6, 200);

	//Add first beams
	for (int i = 0; i < 6; i++) {
		AddBeam(sf::Vector2f(beamPos.x * i, beamPos.y));
	}
	//AddBeam(sf::Vector2f(prisma->getPosition().x, prisma->getPosition().y - 100));
}

//Override Update method from base Component class
void ReflectorBeamManager::Update(float deltaTime) {
	Component::Update(deltaTime);

	//If prism is moving
	if (prismaMovementController->IsMovingRight() || prismaMovementController->IsMovingLeft()) {
		for (auto it = beams.begin(); it != beams.end();) {
			if (it->second != nullptr) {
				//Set line color
				it->second->GetComponent<ReflectorBeam>()->SetLineColor(prismaMovementController->GetCurrentPrismColor());
				//Increase iterator
				it++;
			}
			else {
				it = beams.erase(it);
			}
		}
	}
}

//Adds a beam with a position and rotation
GameObject& ReflectorBeamManager::AddBeam(sf::Vector2f position) {
	//Make new GameObject instance pointer
	GameObject* beam = new GameObject("Beam", SceneManager::GetActiveScene());

	//Set draw index of GameObject
	beam->SetDrawIndex(4);

	//Make new beam instance pointer
	ReflectorBeam* reflectorBeamComponent = new ReflectorBeam(mirrorManager, this, beamIndex);

	//Add components from the beam to the GameObject
	beam->AddComponent(reflectorBeamComponent);

	//Set begin position of line
	reflectorBeamComponent->GetLine()[0].position = position;

	//Set begin line color
	reflectorBeamComponent->SetLineColor(prismaMovementController->GetCurrentPrismColor());

	//Insert beam into beam map and increase beamIndex
	beams.insert(std::pair<int, GameObject*>(beamIndex, beam));
	beamIndex++;

	return *beam;
}

void ReflectorBeamManager::DestroyBeam(GameObject* beam) {
	bool found = false;
	for (auto it = beams.begin(); it != beams.end(); it++) {
		if (it->second == beam) {
			found = true;
			it->second = nullptr;
		}
	}
	SceneManager::GetActiveScene().DestroyGameObject(beam);
}

//Gets the beams map
std::map<int, GameObject*>& ReflectorBeamManager::GetBeams() {
	return beams;
}
