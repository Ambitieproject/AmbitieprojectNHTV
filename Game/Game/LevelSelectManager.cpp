#include "LevelSelectManager.h"
#include "SceneManager.h"

//Constructor
LevelSelectManager::LevelSelectManager() {

}

//Destructor
LevelSelectManager::~LevelSelectManager() {

}

//Override Start method from base Component class
void LevelSelectManager::Start() {
	Component::Start();

	int x = 45;
	int y = 120;

	for (int i = 1; i < 31; i++) {
		BC::Button* button = new BC::Button("../Assets/LevelSelect/levelSelectButtonNormal.png");
		BC::Text* levelNumber = new BC::Text(&font);

		button->GetCurrentButtonSprite().setScale(0.4f, 0.4f);
		button->GetCurrentButtonSprite().setOrigin(button->GetCurrentButtonSprite().getTexture()->getSize().x / 2, button->GetCurrentButtonSprite().getTexture()->getSize().y / 2);
		button->GetCurrentButtonSprite().setPosition(x, y);

		levelNumber->setScale(1, 1);
		levelNumber->setString(std::to_string(i));
		levelNumber->setColor(sf::Color::Black);

		if (i < 10) {
			levelNumber->setPosition(x - 7, y - 20);
		}
		else {
			levelNumber->setPosition(x - 15, y - 20);
		}

		gameObject->AddComponent(button);
		gameObject->AddComponent(levelNumber);

		levelButtons.insert(std::pair<int, BC::Button*>(i, button));

		x = x + 100;
		if (i == 5 || i == 10 || i == 15 || i == 20 || i == 25 || i == 30) {
			y = y + 80;
			x = 45;
		}
	}
	
	hasSelectedLevel = true;
}

//Override Update method from base Component class
void LevelSelectManager::Update(float deltaTime) {
	Component::Update(deltaTime);

	if (hasSelectedLevel) {
		hasSelectedLevel = false;
		
	}
}
