#include "AudioManager.h"

std::map<std::string, BC::Music&> AudioManager::musics;
std::map<std::string, BC::Sound&> AudioManager::sounds;

//Constructor
AudioManager::AudioManager() {
}

//Destructor
AudioManager::~AudioManager() {

}

//Adds music with name to the game
void AudioManager::AddMusic(BC::Music& music, std::string musicName) {
	//For every item in the musics map
	for (auto it = musics.begin(); it != musics.end(); it++) {
		//If first element of item is equal to the parameter name then the item already exists
		if (it->first == musicName) {
			std::cout << "Music with name: " << musicName << " already excists" << std::endl;
			return;
		}
	}

	//If item does not exist then insert the item into the map
	musics.insert(std::pair<std::string, BC::Music&>(musicName, music));
}

//Adds sound with name to the game
void AudioManager::AddSound(BC::Sound& sound, std::string soundName) {
	//For every item in the sound map
	for (auto it = sounds.begin(); it != sounds.end(); it++) {
		//If first element of item is equal to the parameter name then the item already exists
		if (it->first == soundName) {
			std::cout << "Sounds with name: " << soundName << " already excists" << std::endl;
			return;
		}
	}

	//If item does not exist then insert the item into the map
	sounds.insert(std::pair<std::string, BC::Sound&>(soundName, sound));
}

//Get a specific music pointer object
BC::Music* AudioManager::GetMusic(std::string musicName) {
	//For every item in the musics map
	for (auto it = musics.begin(); it != musics.end(); it++) {
		//If first element of item is equal to the parameter name then return the item
		if (it->first == musicName) {
			return &it->second;
		}
	}

	//If item is not found then return a nullptr and cout
	std::cout << "coudn't find music component with name: " << musicName << std::endl;
	return nullptr;
}

//Get a specific sound pointer object
BC::Sound* AudioManager::GetSound(std::string soundName) {
	//For every item in the sound map
	for (auto it = sounds.begin(); it != sounds.end(); it++) {
		//If first element of item is equal to the parameter name then return the item
		if (it->first == soundName) {
			return &it->second;
		}
	}

	//If item is not found then return a nullptr and cout
	std::cout << "coudn't find sound component with name: " << soundName << std::endl;
	return nullptr;
}
