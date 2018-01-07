#include "LevelLoader.h"

//Constructor
LevelLoader::LevelLoader(ReflectorBeamManager* reflectorBeamManager, MirrorManager* mirrorManager) : reflectorBeamManager(reflectorBeamManager), mirrorManager(mirrorManager) {

}

//Destructor
LevelLoader::~LevelLoader() {

}

//Get JSON data and put it inside a Level object
void LevelLoader::SetLevelData(const json& j, Level& level, int iterator) {
	//Set level from JSON Object
	level.level = j[iterator].at("Level").get<int>();
	//Set MirrorsNeededCount from JSON Object
	level.MirrorsNeededCount = j[iterator].at("MirrorsNeededCount").get<int>();

	//For 6 times
	for (int i = 0; i < 6; i++) {
		//Pushback a new sf::Vector2f is the map
		level.LaserPositions.push_back(sf::Vector2f(0, 0));
		//Set LaserPositions x value from JSON Object
		level.LaserPositions[i].x = j[iterator].at("LaserTranslations")[i]["PositionX"].get<float>();
		//Set LaserPositions y value from JSON Object
		level.LaserPositions[i].y = j[iterator].at("LaserTranslations")[i]["PositionY"].get<float>();

		//Pushback a new sf::Vector2f is the map
		level.LaserRotations.push_back(0);
		//Set LaserRotations from JSON Object
		level.LaserRotations[i] = j[iterator].at("LaserTranslations")[i]["Rotation"].get<float>();
	}

	//For the length of the BlockingMirrorsTranslations array zise
	for (int i = 0; i < j[iterator].at("BlockingMirrorsTranslations").size(); i++) {
		//Pushback a new sf::Vector2f is the map
		level.BlockingMirrorsPositions.push_back(sf::Vector2f(0, 0));
		//Set BlockingMirrorsPositions x value from JSON Object
		level.BlockingMirrorsPositions[i].x = j[iterator].at("BlockingMirrorsTranslations")[i]["PositionX"].get<float>();
		//Set BlockingMirrorsPositions y value from JSON Object
		level.BlockingMirrorsPositions[i].y = j[iterator].at("BlockingMirrorsTranslations")[i]["PositionY"].get<float>();

		//Pushback a new sf::Vector2f is the map
		level.BlockingMirrorsRotations.push_back(0);
		//Set BlockingMirrorsRotations from JSON Object
		level.BlockingMirrorsRotations[i] = j[iterator].at("BlockingMirrorsTranslations")[i]["Rotation"].get<float>();
	}
}

//Override Start method from base Component class
void LevelLoader::Start() {
	Component::Start();

	//Load level data
	LoadCurrentLevelData();

	//For 6 times
	for (int i = 0; i < 6; i++) {

		//Create a beam color
		sf::Color beamColor;

		//Switch on the i value
		//Set beamColor depending on the i value
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

		//Add the beame with the all the data the method needs to create a beam
		reflectorBeamManager->AddBeam(currentLevel.LaserPositions[i], currentLevel.LaserRotations[i], beamColor);
	}

	//For the length of BlockingMirrorsPositions map in the currentLevel variable
	for (int i = 0; i < currentLevel.BlockingMirrorsPositions.size(); i++) {
		//Add the beame with the all the data the method needs to create a beam
		Mirror& mirror = mirrorManager->AddMirror(sf::Vector2f(currentLevel.BlockingMirrorsPositions[i].x, currentLevel.BlockingMirrorsPositions[i].y), currentLevel.BlockingMirrorsRotations[i]);
		//Set mirror to be static
		mirror.SetIsStaticObject(true);
	}
}

//Override Update method from base Component class
void LevelLoader::Update(float deltaTime) {
	Component::Update(deltaTime);
}

//Loads the data from a level
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
	SetLevelData(levelData, currentLevel, currentLevelNumber["CurrentLevel"] - 1);
}
