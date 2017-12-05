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

void ReflectorBeam::Update(float deltaTime) {
	Component::Update(deltaTime);

	for (auto it = mirrorManager->GetMirrors().begin(); it != mirrorManager->GetMirrors().end(); it++) {
		it->second->GetComponent<Mirror>()->DrawMirrorLine();
		std::cout << it->second->GetComponent<Mirror>()->GetSlope() << std::endl;
	}


	if (!isCollidingWithMirror) {
		line[1].position = line[0].position - sf::Vector2f(0, Window::GetInstance()->GetWindowSize().y * 5);
	}
}

sf::Vertex* ReflectorBeam::GetLine() {
	return line;
}

void ReflectorBeam::SetLineColor(sf::Color color) {
	line[0].color = color;
	line[1].color = color;
}
