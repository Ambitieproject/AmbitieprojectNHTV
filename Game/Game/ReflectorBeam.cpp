#include "ReflectorBeam.h"
#include "GameObject.h"
#include "ReflectorBeamManager.h"
#include "Window.h"
#include "Equations.h"
#include "SceneManager.h"

//Constructor
ReflectorBeam::ReflectorBeam(ReflectorBeamManager* reflectorBeamManager, int beamIndexInMap, int beamRotation) : reflectorBeamManager(reflectorBeamManager), beamIndexInMap(beamIndexInMap), BeamRotation(beamRotation) {
	NoRotationBeam = false;
}

//Destructor
ReflectorBeam::~ReflectorBeam() {

}

//Override Start method from base Component class
void ReflectorBeam::Start() {
	Component::Start();
}

//Override Update method from base Component class
void ReflectorBeam::Update(float deltaTime) {
	Component::Update(deltaTime);
}

//Destroys laser
void ReflectorBeam::DestroyNewLaser() {
	//If the new beam has a new beam
	if (newBeam->GetComponent<ReflectorBeam>()->newBeam) {
		//Destor that new beam
		newBeam->GetComponent<ReflectorBeam>()->DestroyNewLaser();
	}

	//Destroy new beam
	reflectorBeamManager->DestroyBeam(newBeam);

	//Set new beam equal to a nullptr
	newBeam = nullptr;
}

//Set laser line color
void ReflectorBeam::SetLineColor(sf::Color color) {
	//Set color of point
	line[0].color = color;
	//Set color of point
	line[1].color = color;
}

//Set direction
sf::Vector2f ReflectorBeam::SetDirection(sf::Vector2f direction) {
	//Set direction
	this->direction = direction;
	//Return direction
	return this->direction;
}

//Get the laser line
sf::Vertex* ReflectorBeam::GetLine() {
	return line;
}

//Get direction vector
sf::Vector2f ReflectorBeam::GetDirection() {
	//If no rotation is false
	if(!NoRotationBeam)
		//Set direction equal to vector generated from a rotation
		direction = Equations::CreateDirectionFromRotation(BeamRotation);
	
	//Return direction
	return direction;
}

//Get beam index in map
int ReflectorBeam::GetBeamIndexInMap() {
	return beamIndexInMap;
}
