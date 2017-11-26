#include "ReflectorBeam.h"
#include "GameObject.h"
#include "SceneManager.h"



ReflectorBeam::ReflectorBeam(std::string beamFilePath) : beamFilePath(beamFilePath) {
	
}


ReflectorBeam::~ReflectorBeam()
{
}

void ReflectorBeam::Awake() {
	beam = new BC::Sprite(beamFilePath);
	beam->setPosition(SceneManager::GetActiveScene().FindGameObjectByName("Prisma")->GetComponent<BC::Sprite>()->getPosition());
	beam->setPosition(beam->getPosition().x, beam->getPosition().y - 50);
	GameObject->AddComponent(beam);
}

void ReflectorBeam::Update(float deltaTime) {
	Component::Update(deltaTime);

	beam->setScale(beam->getScale().x, beam->getScale().y - 10 * deltaTime);
}
