#include "GameFlowManager.h"
#include "SceneManager.h"

GameFlowManager::GameFlowManager() {

}


GameFlowManager::~GameFlowManager() {

}

//Override Start method from base Component class
void GameFlowManager::Start() {
	if (SceneManager::GetActiveScene().Name == "MainScene") {
		validationManager = SceneManager::GetActiveScene().FindGameObjectByName("ValidationManager")->GetComponent<ValidationManager>();
	}
}

//Override Update method from base Component class
void GameFlowManager::Update(float deltaTime) {
	std::cout << "reeedd me" << std::endl;
	if (SceneManager::GetActiveScene().Name == "MainScene") {
		
		if (IsGameOver()) {
			
		}
	}
}

bool GameFlowManager::IsGameOver() {
	if (validationManager->Validate()) {
		return true;
	}
	return false;
}
