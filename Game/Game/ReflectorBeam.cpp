#include "ReflectorBeam.h"
#include "GameObject.h"
#include "MirrorManager.h"
#include "ReflectorBeamManager.h"

ReflectorBeam::ReflectorBeam(MirrorManager* mirrorManager, ReflectorBeamManager* reflectorBeamManager) : mirrorManager(mirrorManager), reflectorBeamManager(reflectorBeamManager) {

}

ReflectorBeam::~ReflectorBeam() {

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
