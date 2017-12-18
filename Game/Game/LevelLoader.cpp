#include "LevelLoader.h"



LevelLoader::LevelLoader() {

}


LevelLoader::~LevelLoader() {

}

void to_json(json& j, const Level& level) {
	j["Level"] = level.level;
	j["Translations"] = { { "PositionX", level.Translations[0].x },{ "PositionY", level.Translations[0].y },{ "Rotation", 240 } };
}
void from_json(const json& j, Level& p) {
	p.level = j.at("Level").get<int>();
}

void LevelLoader::Start() {
	Component::Start();

	Level level;

	level.level = 0;
	level.Translations.push_back(sf::Vector2f(83, 100));

	json j;
	to_json(j, level);
	FileReadWrite::WriteJSONToFile("../Assets/JSON/Levels.json", j);
}

void LevelLoader::Update(float deltaTime) {
	Component::Update(deltaTime);
}

