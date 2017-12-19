#include "LevelLoader.h"



LevelLoader::LevelLoader(ReflectorBeamManager* reflectorBeamManager) : reflectorBeamManager(reflectorBeamManager) {

}


LevelLoader::~LevelLoader() {

}

/*
void to_json(json& j, const Level& level, int iterator) {
	j[iterator]["Level"] = iterator + 1;
	j[iterator]["LaserTranslations"][0]["PositionX"] = 83;
	j[iterator]["LaserTranslations"][0]["PositionY"] = 100;
	j[iterator]["LaserTranslations"][0]["Rotation"] = 190;
	j[iterator]["LaserTranslations"][1]["PositionX"] = 83;
	j[iterator]["LaserTranslations"][1]["PositionY"] = 100;
	j[iterator]["LaserTranslations"][1]["Rotation"] = 190;
	j[iterator]["LaserTranslations"][2]["PositionX"] = 83;
	j[iterator]["LaserTranslations"][2]["PositionY"] = 100;
	j[iterator]["LaserTranslations"][2]["Rotation"] = 190;
	j[iterator]["LaserTranslations"][3]["PositionX"] = 83;
	j[iterator]["LaserTranslations"][3]["PositionY"] = 100;
	j[iterator]["LaserTranslations"][3]["Rotation"] = 190;
	j[iterator]["LaserTranslations"][4]["PositionX"] = 83;
	j[iterator]["LaserTranslations"][4]["PositionY"] = 100;
	j[iterator]["LaserTranslations"][4]["Rotation"] = 190;
	j[iterator]["LaserTranslations"][5]["PositionX"] = 83;
	j[iterator]["LaserTranslations"][5]["PositionY"] = 100;
	j[iterator]["LaserTranslations"][5]["Rotation"] = 190;
	j[iterator]["MirrorsNeededCount"] = 5;
}
*/

void from_json(const json& j, Level& level, int iterator) {
	level.level = j[iterator].at("Level").get<int>();
	level.MirrorsNeededCount = j[iterator].at("MirrorsNeededCount").get<int>();

	for (int i = 0; i < 6; i++) {
		level.Positions.push_back(sf::Vector2f(0, 0));
		level.Positions[i].x = j[iterator].at("LaserTranslations")[i]["PositionX"].get<float>();
		level.Positions[i].y = j[iterator].at("LaserTranslations")[i]["PositionY"].get<float>();

		level.Rotations.push_back(0);
		level.Rotations[i] = j[iterator].at("LaserTranslations")[i]["Rotation"].get<float>();
	}
}

void LevelLoader::Start() {
	Component::Start();

	LoadCurrentLevelData();

	for (int i = 0; i < 6; i++) {

		sf::Color beamColor;

		switch (i) {
		case 0:
			beamColor = sf::Color::Red;
			break;
		case 1:
			beamColor = sf::Color(255, 153, 0);
			break;
		case 2:
			beamColor = sf::Color::Yellow;
			break;
		case 3:
			beamColor = sf::Color::Green;
			break;
		case 4:
			beamColor = sf::Color::Blue;
			break;
		case 5:
			beamColor = sf::Color(153, 0, 204);
			break;
		}

		reflectorBeamManager->AddBeam(currentLevel.Positions[i], currentLevel.Rotations[i], beamColor);
	}
}

void LevelLoader::Update(float deltaTime) {
	Component::Update(deltaTime);
}

void LevelLoader::LoadCurrentLevelData() {
	//Level data
	json levelData;
	//CurrentLevelNumber data 
	json currentLevelNumber;

	//Set currentLevenNumber by loading it from json file
	FileReadWrite::GetJSONFromFile("../Assets/JSON/CurrentLevel.json", currentLevelNumber);
	//Set levelData by loading it from json file
	FileReadWrite::GetJSONFromFile("../Assets/JSON/Levels.json", levelData);

	//Set currentLevel data equal to loaded json level data
	from_json(levelData, currentLevel, currentLevelNumber["CurrentLevel"] - 1);
}

