#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>

//Include Audio manage accessibility
#include "AudioManager.h"

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"
#include "BaseComponents.hpp"

#include "ValidationManager.h"
#include "ScoreManager.h"
#include "FileReadWrite.h"
#include "Level.h"

//Include and use for making use of the Modern JSON library from nlohmann
//For more information go to the json hpp file 
#include "json.hpp"
using json = nlohmann::json;

//Game Flow Manager
class GameFlowManager : public Component {
public:
	//Constructor
	GameFlowManager(ScoreManager& scoreManager, ValidationManager& validationManager);
	//Destructor
	~GameFlowManager();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

	//Sends message to the active scene that level transitation can be done or not
	bool FromLevelToMenu();

private:
	//Checks if game is over
	bool IsGameOver();

	//Creates and activates Game Over screen
	void ActivateGameOverScreen();

	//Uploads the score as currency
	void UploadScoreAsCurrency();
	
	//Ends the game
	void EndGame();

	//Pauses the game
	void PauseGame();

private:
	//Score value
	int score;

	//Is game over bool
	bool isGameOver;

	//Local pointer of menu button
	BC::Button* localToMenuButton;

	//ValidationManager reference
	ValidationManager& validationManager;
	//ScoreManager reference
	ScoreManager& scoreManager;
};

