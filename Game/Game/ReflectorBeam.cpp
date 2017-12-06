#include "ReflectorBeam.h"
#include "GameObject.h"
#include "MirrorManager.h"
#include "ReflectorBeamManager.h"
#include "Window.h"

ReflectorBeam::ReflectorBeam(MirrorManager* mirrorManager, ReflectorBeamManager* reflectorBeamManager) : mirrorManager(mirrorManager), reflectorBeamManager(reflectorBeamManager) {
	isCollidingWithMirror = false;
}

ReflectorBeam::~ReflectorBeam() {

}

void ReflectorBeam::Start() {
	Component::Start();

	sf::Vector2f dir = GetDirection();
	sf::Vector2f newPos = line[0].position + sf::Vector2f(0, -500);
	newPos.x * dir.x;
	newPos.y * dir.y;
	line[1].position = newPos;
}

void ReflectorBeam::Update(float deltaTime) {
	Component::Update(deltaTime);

	for (auto it = mirrorManager->GetMirrors().begin(); it != mirrorManager->GetMirrors().end(); it++) {
		//it->second->GetComponent<Mirror>()->DrawMirrorLine();
		//std::cout << it->second->GetComponent<Mirror>()->GetSlope() << std::endl;
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
		
	}
	else {
		x = cos(90 * PI / 180.0);
		y = cos(90 * PI / 180.0);
	}

	std::cout << x << " " << y << std::endl;

	return sf::Vector2f(x, y);
}
