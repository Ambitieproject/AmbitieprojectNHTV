#include "Component.h"

//Constructor
Component::Component() {
	//Set enabled state of component to be enabled
	Enabled = true;
}

//Destructor
Component::~Component() {

}

//Awake method of this comopnent
void Component::Awake() {

}

//Start method of this component
void Component::Start() {
	//Set CanStart state to be true
	DidStart = true;
}

//Update method of this component
void Component::Update(float deltaTime) {

}