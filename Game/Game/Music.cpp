#include "Music.h"

using namespace BC;

//Constructor
Music::Music(std::string pathToMusic) {
	openFromFile(pathToMusic);
}

//Destructor
Music::~Music() {

}

//Override Start method from base Component class
void Music::Start() {
	Component::Start();
}

//Override Update method from base Component class
void Music::Update(float deltaTime) {
	Component::Update(deltaTime);
}
