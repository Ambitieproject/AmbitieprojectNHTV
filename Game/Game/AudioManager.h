#pragma once

#include <iostream>
#include <map>

#include "BaseComponents.hpp"

class AudioManager {
public:
	AudioManager();
	~AudioManager();

	static void AddMusic(BC::Music& music, std::string musicName);
	static void AddSound(BC::Sound& sound, std::string soundName);

	static BC::Music* GetMusic(std::string musicName);
	static BC::Sound* GetSound(std::string soundName);

private:
	static std::map<std::string, BC::Music&> musics;
	static std::map<std::string, BC::Sound&> sounds;
};

