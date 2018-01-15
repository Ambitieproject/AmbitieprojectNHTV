#pragma once

#include <iostream>
#include <map>

//Include all Base Components
#include "BaseComponents.hpp"

//AudioManager, takes care of storing and editing audio throughout the whole game
class AudioManager {
public:
	//Constructor
	AudioManager();
	//Destructor
	~AudioManager();

	//Adds music with name to the game
	static void AddMusic(BC::Music& music, std::string musicName);
	//Adds sound with name to the game
	static void AddSound(BC::Sound& sound, std::string soundName);

	//Get a specific music pointer object
	static BC::Music* GetMusic(std::string musicName);
	//Get a specific sound pointer object
	static BC::Sound* GetSound(std::string soundName);

private:
	//Map that holds all the music objects with a name
	static std::map<std::string, BC::Music&> musics;
	//Map that holds all the sound objects with a name
	static std::map<std::string, BC::Sound&> sounds;
};

