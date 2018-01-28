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
	//If game is over
	if (IsGameOver() && !isGameOver) {
		//End game
		EndGame();
	}
}

//Sends message to the active scene that level transitation can be done or not
bool GameFlowManager::FromLevelToMenu() {
	//If game is over and to menu button is clicked return true
	if (isGameOver && localToMenuButton->IsClicked()) {
		//Play click sound
		AudioManager::GetSound("ButtonClickForwardSound")->play();
		//Set is game over
		isGameOver = false;
		return true;
	}
	//Else return false
	else {
		return false;
	}
}

//Checks if game is over
bool GameFlowManager::IsGameOver() {
	//If validationManager validate method return true
	//return true
	if (validationManager.Validate()) {
		return true;
	}
	//Else return false
	else {
		return false;
	}
}

//Creates and activates Game Over screen
void GameFlowManager::ActivateGameOverScreen() {
	//Create GameObject and Components
	GameObject* go = new GameObject("GameOverScreen", gameObject->GetScene());

	BC::Sprite* gameOverScreenSprite = new BC::Sprite("../Assets/Art/Level/ScoreOverlay.png");
	
	BC::Font* font = new BC::Font("../Assets/Fonts/Century Gothic.ttf");
	
	BC::Text* scoreText = new BC::Text(font);
	BC::Text* scoreTextStatic = new BC::Text(font);
	
	BC::Text* mirrorCountText = new BC::Text(font);
	BC::Text* mirrorCountTextStatic = new BC::Text(font);

	BC::Text* toManyMirrorsText = new BC::Text(font);

	localToMenuButton = new BC::Button("../Assets/Art/Level/Buttons//ToMenu/ButtonToMenuIdle.png", "../Assets/Art/Level/Buttons//ToMenu/ButtonToMenuHovered.png", "../Assets/Art/Level/Buttons//ToMenu/ButtonToMenuPressed.png");

	//Set draw index of GameObjects
	go->SetDrawIndex(0);
	
	//Set default values of gameOverScreenSprite
	gameOverScreenSprite->setScale(0.6f, 0.6f);
	gameOverScreenSprite->setOrigin(gameOverScreenSprite->GetTexture().getSize().x / 2, gameOverScreenSprite->GetTexture().getSize().y / 2);
	gameOverScreenSprite->setPosition(Window::GetWindowSize().x / 2, Window::GetWindowSize().y / 2);

	//Set score equal to result of method in scoreManager class
	score = scoreManager.GetFinalScore();

	//Set default value of scoreText
	scoreText->setString(std::to_string(score));
	scoreText->setColor(sf::Color::White);
	sf::FloatRect bounds = scoreText->getGlobalBounds();
	scoreText->setPosition((Window::GetWindowSize().x / 2) - (bounds.width / 2) + 55, Window::GetWindowSize().y / 2 - 100);

	//Set default values of scoreTextStatic
	scoreTextStatic->setScale(0.8f, 0.8f);
	scoreTextStatic->setPosition(Window::GetWindowSize().x / 2 - 110, Window::GetWindowSize().y / 2 - 95);
	scoreTextStatic->setString("Score:");
	scoreTextStatic->setColor(sf::Color::White);

	//Set default value of mirrorCountText
	mirrorCountText->setString(std::to_string(scoreManager.GetMirrorsUsed()));
	mirrorCountText->setColor(sf::Color::White);
	bounds = mirrorCountText->getGlobalBounds();
	mirrorCountText->setPosition((Window::GetWindowSize().x / 2) - (bounds.width / 2) + 55, Window::GetWindowSize().y / 2 - 45);

	//Set default values of mirrorCountTextStatic
	mirrorCountTextStatic->setScale(0.8f, 0.8f);
	mirrorCountTextStatic->setPosition(Window::GetWindowSize().x / 2 - 110, Window::GetWindowSize().y / 2 - 40);
	mirrorCountTextStatic->setString("Mirrors used:");
	mirrorCountTextStatic->setColor(sf::Color::White);

	//Calculate mirrorCount
	int mirrorCount = scoreManager.GetMirrorsUsed() - (scoreManager.GetMaximumMirrorsAllowed() + scoreManager.GetExtraMirrorsFromShop());

	if (mirrorCount > 0) {
		//Set default values
		toManyMirrorsText->setScale(0.6f, 0.6f);
		bounds = toManyMirrorsText->getGlobalBounds();
		toManyMirrorsText->setPosition((Window::GetWindowSize().x / 2) - (bounds.width / 2) - 20, Window::GetWindowSize().y / 2 + 20);
		toManyMirrorsText->setString(std::to_string(mirrorCount) + " mirrors to much");
		toManyMirrorsText->setColor(sf::Color::Red);
	}

	//Set default values of the localToMenuButton
	localToMenuButton->GetCurrentButtonSprite().setScale(0.3f, 0.3f);
	localToMenuButton->GetCurrentButtonSprite().setOrigin(localToMenuButton->GetCurrentButtonSprite().getTexture()->getSize().x / 2, localToMenuButton->GetCurrentButtonSprite().getTexture()->getSize().y / 2);
	localToMenuButton->GetCurrentButtonSprite().setPosition(Window::GetWindowSize().x / 2, Window::GetWindowSize().y / 2 + 80);
	
	//Add Components to the GameObject
	go->AddComponent(gameOverScreenSprite);
	go->AddComponent(scoreText);
	go->AddComponent(scoreTextStatic);
	go->AddComponent(mirrorCountText);
	go->AddComponent(mirrorCountTextStatic);
	go->AddComponent(localToMenuButton);

	//If you used to many mirrors add the to many mirrors text
	if (mirrorCount > 0) {
		go->AddComponent(toManyMirrorsText);
	}
}

//Ends the game
void GameFlowManager::EndGame() {
	//Set Game Over to be true
	isGameOver = true;

	//Run all necessary methods for the game to be over
	ActivateGameOverScreen();
	UploadScoreAsCurrency();
	PauseGame();
}

//Uploads the score as currency
void GameFlowManager::UploadScoreAsCurrency() {
	//Create JSON object
	json json;
	//Get data from file into JSON object
	FileReadWrite::GetJSONFromFile("../Assets/JSON/Currency.json", json);

	//Make temp score variable
	int currentScore = json["Currency"];
	//Calculate new score
	int newScore = currentScore + score;
	//Set value of JSON object equal to the new score
	json["Currency"] = newScore;

	//Upload JSON object
	FileReadWrite::WriteJSONToFile("../Assets/JSON/Currency.json", json);
}

//Pauses the game
void GameFlowManager::PauseGame() {
	//Disable Components
	gameObject->GetComponent<TimeManager>()->Enabled = false;
	gameObject->GetComponent<MirrorManager>()->Enabled = false;
}
