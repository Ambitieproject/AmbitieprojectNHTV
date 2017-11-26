#include "ReflectorBeam.h"
#include "GameObject.h"



ReflectorBeam::ReflectorBeam(std::string beamFilePath) : beamFilePath(beamFilePath) {
	
}


ReflectorBeam::~ReflectorBeam()
{
}

void ReflectorBeam::Awake() {
	BC::Sprite beam = BC::Sprite(beamFilePath);
	GameObject->AddComponent(&beam);
}
