#include "LevelSelectManager.h"

//Constructor
LevelSelectManager::LevelSelectManager() {

}

//Destructor
LevelSelectManager::~LevelSelectManager() {

}

//Override Start method from base Component class
void LevelSelectManager::Start() {
	Component::Start();

	//Call create buttons method
	CreateLevelButtons();

	//Set default methods
	hasSelectedLevel = false;
}

//Override Update method from base Component class
void LevelSelectManager::Update(float deltaTime) {
	Component::Update(deltaTime);

	//For every button check if that button is clicked
	for (auto it = levelButtons.begin(); it != levelButtons.end(); it++) {
		if (it->second->IsClicked()) {
			currentSelectedLevel = it->first;
			hasSelectedLevel = true;
		}
	}
}

//Returns the state of level selected
bool LevelSelectManager::HasSelectedLevel() {
	return hasSelectedLevel;
}

//Gets the current selected level number
int LevelSelectManager::GetCurrentSelectedLevel() {
	return currentSelectedLevel;
}

//Creates level buttons
void LevelSelectManager::CreateLevelButtons() {
	//Start x and y position values
	int x = 120;
	int y = 200;

	//Level data
	json levelData;

	//Set levelData by loading it from json file
	FileReadWrite::GetJSONFromFile("../Assets/JSON/Levels.json", levelData);

	//For the amount of buttons you want + 1 
	for (int i = 1; i < levelData.size() + 1; i++) {
		//Create button and text
		BC::Button* button = new BC::Button("../Assets/Art/LevelSelect/Buttons/levelSelectButtonIdle.png", "../Assets/Art/LevelSelect/Buttons/levelSelectButtonHovered.png");
		BC::Text* levelNumber = new BC::Text(&font);

		//Set button standard values
		button->GetCurrentButtonSprite().setScale(1.0f, 1.0f);
		button->GetCurrentButtonSprite().setOrigin(button->GetCurrentButtonSprite().getTexture()->getSize().x / 2, button->GetCurrentButtonSprite().getTexture()->getSize().y / 2);
		button->GetCurrentButtonSprite().setPosition(x, y);

		//Set text standard values
		levelNumber->setScale(1, 1);
		levelNumber->setString(std::to_string(i));
		levelNumber->setColor(sf::Color::Black);

		//Reset positions based on the number the button has
		if (i < 10) {
			levelNumber->setPosition(x - 7, y - 20);
		}
		else {
			levelNumber->setPosition(x - 15, y - 20);
		}

		//Add components
		gameObject->AddComponent(button);
		gameObject->AddComponent(levelNumber);

		//Insert pair into map
		levelButtons.insert(std::pair<int, BC::Button*>(i, button));

		//Increase x value
		x = x + 125;

		//Increase y value and reset x value based on the current i value
		if (i == 3 || i == 6 || i == 9 || i == 12 || i == 15 || i == 18) {
			y = y + 125;
			x = 120;
		}
	}
}
