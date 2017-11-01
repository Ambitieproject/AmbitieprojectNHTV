#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject& gameObject) : gameObject(gameObject) {
	gameObject.AddComponent(this);
}

Component::~Component() {

}

//Start method of this component
void Component::Start() {

}

//Update method of this component
void Component::Update(float deltaTime) {

}

GameObject& Component::GetGameObject() {
	return gameObject;
}