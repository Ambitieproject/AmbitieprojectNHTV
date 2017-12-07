#include "ReflectorBeam.h"
#include "GameObject.h"
#include "MirrorManager.h"
#include "ReflectorBeamManager.h"
#include "Window.h"
#include "Equations.h"

ReflectorBeam::ReflectorBeam(MirrorManager* mirrorManager, ReflectorBeamManager* reflectorBeamManager) : mirrorManager(mirrorManager), reflectorBeamManager(reflectorBeamManager) {
	isCollidingWithMirror = false;
}

ReflectorBeam::~ReflectorBeam() {

}

void ReflectorBeam::Start() {
	Component::Start();

	if (!isCollidingWithMirror) {
		sf::Vector2f dir = GetDirection();

		std::cout << "direction of laser: " << GetDirection().x << " / " << GetDirection().y << std::endl;
		
		sf::Vector2f newPos = line[0].position + sf::Vector2f(dir.x * 300, dir.y * 300);
		line[1].position = newPos;
	}
}

void ReflectorBeam::Update(float deltaTime) {
	Component::Update(deltaTime);

	for (auto it = mirrorManager->GetMirrors().begin(); it != mirrorManager->GetMirrors().end(); it++) {
		
		sf::Vector2f p1 = it->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(it->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(0));
		sf::Vector2f p2 = it->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(it->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(1));

		bool collide = Equations::LineCollide(line[0].position, line[0].position + GetDirection(), p1, p2);

		if (collide) {
			std::cout << "thanks David" << std::endl;
		}
		
		//Draw border of calculating at the mirror
		it->second->GetComponent<Mirror>()->DrawMirrorLine();
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
		x = sin(mirrorSpawningFrom->GetComponent<BC::Sprite>()->getRotation());
		y = cos(mirrorSpawningFrom->GetComponent<BC::Sprite>()->getRotation());
		y = -y;
	}
	else {
		x = sin(120);
		y = cos(120);
		y = -y;
	}

	return sf::Vector2f(x, y);
}
