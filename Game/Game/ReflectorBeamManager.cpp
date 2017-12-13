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
	mirrorManager = SceneManager::GetActiveScene().FindGameObjectByName("MirrorManager")->GetComponent<MirrorManager>();
	colorManager = SceneManager::GetActiveScene().FindGameObjectByName("ColorManager")->GetComponent<ColorManager>();

	//Set begin values
	beamIndex = 0;

	//Add beams
	for (int i = 0; i != 6; i++) {
		sf::Vector2f position;
		sf::Color color;
		switch (i) {
		case 0:
			position = sf::Vector2f(83 * (i + 1), 90);
			color = sf::Color::Red;
			break;
		case 1:
			position = sf::Vector2f(83 * (i + 1), 90);
			color = sf::Color(255, 153, 0);
			break;
		case 2:
			position = sf::Vector2f(83 * (i + 1), 90);
			color = sf::Color::Yellow;
			break;
		case 3:
			position = sf::Vector2f(83 * (i + 1), 90);
			color = sf::Color::Green;
			break;
		case 4:
			position = sf::Vector2f(83 * (i + 1), 90);
			color = sf::Color::Blue;
			break;
		case 5:
			position = sf::Vector2f(83 * (i + 1), 90);
			color = sf::Color(153, 0, 204);
			break;
		}

		AddBeam(position, color);
	}
}

//Override Update method from base Component class
void ReflectorBeamManager::Update(float deltaTime) {
	Component::Update(deltaTime);

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
GameObject& ReflectorBeamManager::AddBeam(sf::Vector2f position, sf::Color color) {
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
	reflectorBeamComponent->SetLineColor(color);

	//Insert beam into beam map and increase beamIndex
	beams.insert(std::pair<int, GameObject*>(beamIndex, beam));
	beamIndex++;

	return *beam;
}

//Destroy a beam
void ReflectorBeamManager::DestroyBeam(GameObject* beam) {
	bool found = false;
	for (auto it = beams.begin(); it != beams.end(); it++) {
		if (it->second == beam) {
			found = true;
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
