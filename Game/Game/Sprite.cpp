#include "Sprite.h"
#include "Scene.h"

using namespace BC;

//Constructor with values to be added for a Sprite to be created
Sprite::Sprite(std::string _pathToSPrite, bool _isStatic) {
	//Load texture from a file path
	texture.loadFromFile(_pathToSPrite);
	//Set texture to sprite 
	sprite.setTexture(texture);
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

//SetFillScale Method that fills the scale of the sprite
void Sprite::SetFillScale(int x, int y) {
	sprite.setTextureRect(sf::IntRect(0, 0, x, y));
}

//Set position of sprite method
void Sprite::SetPosition(float x, float y) {
	sprite.setPosition(x, y);
}

//Gets the sprite variable
sf::Sprite& Sprite::GetSprite() {
	return sprite;
}

//Gets the texture variable
sf::Texture& Sprite::GetTexture() {
	return texture;
}