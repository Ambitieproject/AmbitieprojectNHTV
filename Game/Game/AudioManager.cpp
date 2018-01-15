#include "AudioManager.h"

std::map<std::string, BC::Music&> AudioManager::musics;
std::map<std::string, BC::Sound&> AudioManager::sounds;


AudioManager::AudioManager()
{
}


AudioManager::~AudioManager()
{
}

void AudioManager::AddMusic(BC::Music& music, std::string musicName) {
	for (auto it = musics.begin(); it != musics.end(); it++) {
		if (it->first == musicName) {
			std::cout << "Music with name: " << musicName << " already excists" << std::endl;
			return;
		}
	}

	musics.insert(std::pair<std::string, BC::Music&>(musicName, music));
}

void AudioManager::AddSound(BC::Sound& sound, std::string soundName) {
	for (auto it = sounds.begin(); it != sounds.end(); it++) {
		if (it->first == soundName) {
			std::cout << "Sounds with name: " << soundName << " already excists" << std::endl;
			return;
		}
	}

	sounds.insert(std::pair<std::string, BC::Sound&>(soundName, sound));
}

BC::Music* AudioManager::GetMusic(std::string musicName) {
	for (auto it = musics.begin(); it != musics.end(); it++) {
		if (it->first == musicName) {
			return &it->second;
		}
	}

	std::cout << "coudn't find music component with name: " << musicName << std::endl;
	return nullptr;
}

BC::Sound* AudioManager::GetSound(std::string soundName) {
	for (auto it = sounds.begin(); it != sounds.end(); it++) {
		if (it->first == soundName) {
			return &it->second;
		}
	}

	std::cout << "coudn't find sound component with name: " << soundName << std::endl;
	return nullptr;
}
