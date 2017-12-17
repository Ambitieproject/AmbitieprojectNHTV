#include "ScoreManager.h"
#include "GameObject.h"

//Constructor
ScoreManager::ScoreManager(MirrorManager& mirrorManager, TimeManager& timeManager) : mirrorManager(mirrorManager), timeManager(timeManager) {

}

//Destructor
ScoreManager::~ScoreManager() {

}

//Override Start method from base Component class
void ScoreManager::Start() {
	//Setting variables to start value
	score = 0;
	maxScore = 10000;
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

//Gets the final score
int ScoreManager::GetFinalScore() {
	AdjustScore(maxScore);
	
	int mirrorCount = mirrorManager.GetMirrors().size() - 3;

	if (mirrorCount > 0) {
		for (int i = 0; i < mirrorCount; i++) {
			AdjustScore(-100);
		}
	}

	int timeToDecrase = timeManager.GetTimeInSeconds() - 10;

	if (timeToDecrase > 0) {
		AdjustScore(-timeToDecrase);
	}
	
	if (score > 0) {
		return score;
	}
	else {
		return 0;
	}
}
