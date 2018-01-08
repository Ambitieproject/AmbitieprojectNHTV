#include "ReflectorBeam.h"
#include "GameObject.h"
#include "ReflectorBeamManager.h"
#include "Window.h"
#include "Equations.h"
#include "SceneManager.h"

ReflectorBeam::ReflectorBeam(ReflectorBeamManager* reflectorBeamManager, int beamIndexInMap, int beamRotation) : reflectorBeamManager(reflectorBeamManager), beamIndexInMap(beamIndexInMap), beamRotation(beamRotation) {
	isCollidingWithMirror = false;
}

ReflectorBeam::~ReflectorBeam() {

}

void ReflectorBeam::Start() {
	Component::Start();
}

void ReflectorBeam::Update(float deltaTime) {
	Component::Update(deltaTime);
}

sf::Vertex* ReflectorBeam::GetLine() {
	return line;
}

void ReflectorBeam::SetLineColor(sf::Color color) {
	line[0].color = color;
	line[1].color = color;
}

sf::Vector2f ReflectorBeam::GetDirection() {
	return Equations::CreateDirectionFromRotation(beamRotation);
}

int ReflectorBeam::GetBeamIndexInMap() {
	return beamIndexInMap;
}

void ReflectorBeam::DestroyNewLaser() {
	if (newBeam->GetComponent<ReflectorBeam>()->newBeam) {
		newBeam->GetComponent<ReflectorBeam>()->DestroyNewLaser();
	}

	reflectorBeamManager->DestroyBeam(newBeam);
	
	newBeam = nullptr;
}
