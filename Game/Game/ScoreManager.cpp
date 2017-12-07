#include "ScoreManager.h"
#include "GameObject.h"

//Constructor
ScoreManager::ScoreManager() {

}

//Destructor
ScoreManager::~ScoreManager() {

}

//Override Start method from base Component class
void ScoreManager::Start() {
	//Getting component
	scoreText = gameObject->GetComponent<BC::Text>();

	//Setting variables to start value
	score = 0;
	scoreText->setString(std::to_string(score));
}

//Override Update method from base Component class
void ScoreManager::Update(float deltaTime) {

}

//Adjusts score by a specific parameter
int ScoreManager::AdjustScore(int adjustment) {
	score = score + adjustment;
	return score;
}

//Gets the score
int ScoreManager::GetScore() {
	return score;
}
