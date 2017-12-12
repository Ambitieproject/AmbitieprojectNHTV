#include "ReflectorBeam.h"
#include "GameObject.h"
#include "MirrorManager.h"
#include "ReflectorBeamManager.h"
#include "Window.h"
#include "Equations.h"
#include "SceneManager.h"

ReflectorBeam::ReflectorBeam(MirrorManager* mirrorManager, ReflectorBeamManager* reflectorBeamManager, int beamIndexInMap) : mirrorManager(mirrorManager), reflectorBeamManager(reflectorBeamManager), beamIndexInMap(beamIndexInMap) {
	isCollidingWithMirror = false;
}

ReflectorBeam::~ReflectorBeam() {

}

void ReflectorBeam::Start() {
	Component::Start();
}

void ReflectorBeam::Update(float deltaTime) {
	Component::Update(deltaTime);

	bool nobodyCollides = false;

	for (auto it = mirrorManager->GetMirrors().begin(); it != mirrorManager->GetMirrors().end(); it++) {
		GameObject* mirror = it->second;

		if (mirror != mirrorSpawningFrom) {
			sf::Vector2f p0 = it->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(it->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(0));
			sf::Vector2f p1 = it->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(it->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(1));
			sf::Vector2f p2 = it->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(it->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(2));
			sf::Vector2f p3 = it->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(it->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(3));

			

			bool frontsideMirrorCollider = Equations::LineCollide(line[0].position, line[1].position, line[0].position + GetDirection(), p0, p1, *it->second->GetComponent<Mirror>());
			bool backsideMirrorCollider = Equations::LineCollide(line[0].position, line[1].position, line[0].position + GetDirection(), p2, p3, *it->second->GetComponent<Mirror>());
			bool rightsideMirrorCollider = Equations::LineCollide(line[0].position, line[1].position, line[0].position + GetDirection(), p1, p2, *it->second->GetComponent<Mirror>());
			bool leftsideMirrorCollider = Equations::LineCollide(line[0].position, line[1].position, line[0].position + GetDirection(), p0, p3, *it->second->GetComponent<Mirror>());

			if(frontsideMirrorCollider) {
				std::cout << "front" << std::endl;
				nobodyCollides = true;
				reflectingMirror = mirror;
				line[1].position = Equations::pointOfIntersection;;
				if (!newBeam) {
					newBeam = &reflectorBeamManager->AddBeam(Equations::pointOfIntersection, line[0].color);
					newBeam->GetComponent<ReflectorBeam>()->mirrorSpawningFrom = mirror;
				}
				else {
					newBeam->GetComponent<ReflectorBeam>()->line[0].position = Equations::pointOfIntersection;;
				}
			}
		}
	}

	if (!nobodyCollides) {
		reflectingMirror = nullptr;
	}

	if (!reflectingMirror) {
		line[1].position = line[0].position + sf::Vector2f(GetDirection().x * 1000, GetDirection().y * 1000);

		if (newBeam) {
			DestroyNewLaser();
		}
	}
}

sf::Vertex* ReflectorBeam::GetLine() {
	return line;
}

void ReflectorBeam::SetLineColor(sf::Color color) {
	line[0].color = color;
	line[1].color = color;
}

sf::Vector2f ReflectorBeam::GetDirection() {

	float x = 0;
	float y = 0;

	if (mirrorSpawningFrom) {
		x = sin(mirrorSpawningFrom->GetComponent<BC::Sprite>()->getRotation() * PI / 180);
		y = cos(mirrorSpawningFrom->GetComponent<BC::Sprite>()->getRotation() * PI / 180);
		y = -y;
	}
	else {
		x = sin(225 * PI / 180);
		y = cos(225 * PI / 180);
		y = -y;
	}

	return sf::Vector2f(x, y);
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
