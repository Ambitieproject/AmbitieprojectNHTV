#include "ReflectorBeamManager.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Window.h"

//Constructor
ReflectorBeamManager::ReflectorBeamManager() {
	
}

//Destructor
ReflectorBeamManager::~ReflectorBeamManager() {

}

//Override Start method from base Component class
void ReflectorBeamManager::Start() {
	//Setting references
	prisma = SceneManager::GetActiveScene().FindGameObjectByName("Prisma")->GetComponent<BC::Sprite>();

	//Set begin values
	beamIndex = 0;
}

//Override Update method from base Component class
void ReflectorBeamManager::Update(float deltaTime) {
	Component::Update(deltaTime);

	//For every beam
	//If beam is not equal to a nullpltr then increase iterator
	//Else erase beam object from the map
	for (auto it = beams.begin(); it != beams.end();) {
		if (it->second != nullptr) {
			it++;
		}
		else {
			it = beams.erase(it);
		}
	}
}

//Adds a beam with a position and rotation
GameObject& ReflectorBeamManager::AddBeam(sf::Vector2f position, int rotation, sf::Color color) {
	//Make new GameObject instance pointer
	GameObject* beam = new GameObject("Beam", SceneManager::GetActiveScene());

	//Set draw index of GameObject
	beam->SetDrawIndex(4);

	//Make new beam instance pointer
	ReflectorBeam* reflectorBeamComponent = new ReflectorBeam(this, beamIndex, rotation);

	//Set direction of mirror
	reflectorBeamComponent->SetDirection(Equations::CreateDirectionFromRotation(rotation));

	//Add components from the beam to the GameObject
	beam->AddComponent(reflectorBeamComponent);

	//Set begin position of line
	reflectorBeamComponent->GetLine()[0].position = position;

	//Set begin line color
	reflectorBeamComponent->SetLineColor(color);

	//Insert beam into beam map and increase beamIndex
	beams.insert(std::pair<int, GameObject*>(beamIndex, beam));
	beamIndex++;

	return *beam;
}

//Destroy a beam
void ReflectorBeamManager::DestroyBeam(GameObject* beam) {
	//For each beam
	for (auto it = beams.begin(); it != beams.end(); it++) {
		//If iterator is equal to the parameter beam
		//then make the beam a nullptr
		if (it->second == beam) {
			it->second = nullptr;
		}
	}
	//Call destroy GameObject method from scene class
	SceneManager::GetActiveScene().DestroyGameObject(beam);
}

//Gets the beams map
std::map<int, GameObject*>& ReflectorBeamManager::GetBeams() {
	return beams;
}
