#include "GameFlowManager.h"
#include "SceneManager.h"
#include "Window.h"

//Constructor
GameFlowManager::GameFlowManager(ScoreManager& scoreManager, ValidationManager& validationManager) : scoreManager(scoreManager), validationManager(validationManager) {

}

//Destructor
GameFlowManager::~GameFlowManager() {

}

//Override Start method from base Component class
void GameFlowManager::Start() {
	isGameOver = false;
}

//Override Update method from base Component class
void GameFlowManager::Update(float deltaTime) {
	if (IsGameOver() && !isGameOver) {
		EndGame();
	}
}

bool GameFlowManager::FromLevelToScene() {
	if (isGameOver && localToMenuButton->IsClicked()) {
		isGameOver = false;
		return true;
	}
	else {
		return false;
	}
}

bool GameFlowManager::IsGameOver() {
	//return true;
	
	if (validationManager.Validate()) {
		return true;
	}
	return false;
	
}

void GameFlowManager::ActivateGameOverScreen() {
	std::cout << "game over" << std::endl;

	GameObject* go = new GameObject("GameOverScreen", gameObject->GetScene());
	BC::Sprite* gameOverScreenSprite = new BC::Sprite("../Assets/Level/ScoreOverlay.png");

	BC::Font* font = new BC::Font("../Assets/Fonts/Myriad Pro Regular.ttf");
	
	BC::Text* scoreText = new BC::Text(font);
	BC::Text* scoreTextStatic = new BC::Text(font);

	localToMenuButton = new BC::Button("../Assets/Level/Buttons/ButtonToMenuIdle.png", "../Assets/Level/Buttons/ButtonToMenuHovered.png", "../Assets/Level/Buttons/ButtonToMenuPressed.png");

	go->SetDrawIndex(0);
	
	gameOverScreenSprite->setScale(0.6f, 0.6f);
	gameOverScreenSprite->setOrigin(gameOverScreenSprite->GetTexture().getSize().x / 2, gameOverScreenSprite->GetTexture().getSize().y / 2);
	gameOverScreenSprite->setPosition(Window::GetInstance()->GetWindowSize().x / 2, Window::GetInstance()->GetWindowSize().y / 2);

	scoreText->setString(std::to_string(scoreManager.GetFinalScore()));
	scoreText->setColor(sf::Color::Black);

	scoreTextStatic->setScale(0.8f, 0.8f);
	scoreTextStatic->setPosition(Window::GetInstance()->GetWindowSize().x / 2 - 140, Window::GetInstance()->GetWindowSize().y / 2 - 95);
	scoreTextStatic->setString("Score:");
	scoreTextStatic->setColor(sf::Color::Black);

	localToMenuButton->GetCurrentButtonSprite().setScale(0.6f, 0.6f);
	localToMenuButton->GetCurrentButtonSprite().setOrigin(localToMenuButton->GetCurrentButtonSprite().getTexture()->getSize().x / 2, localToMenuButton->GetCurrentButtonSprite().getTexture()->getSize().y / 2);
	localToMenuButton->GetCurrentButtonSprite().setPosition(Window::GetInstance()->GetWindowSize().x / 2, Window::GetInstance()->GetWindowSize().y / 2 + 50);
	

	//Get bounds of text content
	sf::FloatRect bounds = scoreText->getGlobalBounds();
	//Setting position in center based on bounds
	scoreText->setPosition((Window::GetInstance()->GetWindowSize().x / 2) - (bounds.width / 2) + 90, Window::GetInstance()->GetWindowSize().y / 2 - 100);

	go->AddComponent(gameOverScreenSprite);
	go->AddComponent(scoreText);
	go->AddComponent(scoreTextStatic);
	go->AddComponent(localToMenuButton);
}

void GameFlowManager::EndGame(){
	isGameOver = true;
	ActivateGameOverScreen();
	PauseGame();
}

void GameFlowManager::PauseGame() {
	gameObject->GetComponent<TimeManager>()->Enabled = false;
	gameObject->GetComponent<MirrorManager>()->Enabled = false;
}
