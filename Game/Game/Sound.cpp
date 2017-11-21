#include "Sound.h"

using namespace BC;

//Constructor
Sound::Sound(std::string pathToSound) {
	SoundBuffer.loadFromFile(pathToSound);
	setBuffer(SoundBuffer);
}

//Destructor
Sound::~Sound() {

}

//Override Start method from base Component class
void Sound::Start() {
	Component::Start();
}

//Override Update method from base Component class
void Sound::Update(float deltaTime) {
	Component::Update(deltaTime);
}

//Gets the SoundBuffer by reference
sf::SoundBuffer& Sound::GetSoundBuffer() {
	return SoundBuffer;
}
