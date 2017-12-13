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
	int x = 45;
	int y = 120;

	//For the amount of buttons you want + 1 
	for (int i = 1; i < 31; i++) {
		//Create button and text
		BC::Button* button = new BC::Button("../Assets/LevelSelect/levelSelectButtonNormal.png");
		BC::Text* levelNumber = new BC::Text(&font);

		//Set button standard values
		button->GetCurrentButtonSprite().setScale(0.4f, 0.4f);
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
		x = x + 100;

		//Increase y value and reset x value based on the current i value
		if (i == 5 || i == 10 || i == 15 || i == 20 || i == 25 || i == 30) {
			y = y + 80;
			x = 45;
		}
	}
}
