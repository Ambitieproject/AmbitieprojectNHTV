#include "Sprite.h"
#include "Scene.h"

//Use Base Components namespace
using namespace BC;

//Constructor with values to be added for a Sprite to be created
Sprite::Sprite(std::string _pathToSPrite) {
	//Load texture from a file path
	texture.loadFromFile(_pathToSPrite);
	//Set texture to sprite 
	setTexture(texture);
}

//Destructor
Sprite::~Sprite() {

}

//Override Start method from base Component class
void Sprite::Start() {
	Component::Start();
}

//Override Update method from base Component class
void Sprite::Update(float deltaTime) {
	Component::Update(deltaTime);
}

//Gets the texture variable
sf::Texture & BC::Sprite::GetTexture() {
	return texture;
}
