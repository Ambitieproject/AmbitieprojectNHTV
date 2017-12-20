#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"
#include "BaseComponents.hpp"

#include "ValidationManager.h"
#include "ScoreManager.h"
#include "FileReadWrite.h"
#include "Level.h"

//Include and use for making use of the Modern JSON library frmo nlohmann
//For more information go to the json hpp file 
#include "json.hpp"
using json = nlohmann::json;

struct Test {
	int i = 9;
	std::string hoi = "test";
};

//Game Manager
class GameFlowManager : public Component {
public:
	GameFlowManager(ScoreManager& scoreManager, ValidationManager& validationManager);
	~GameFlowManager();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

	bool FromLevelToScene();

private:
	bool IsGameOver();

	void ActivateGameOverScreen();
	void UploadScoreAsCurrency();
	void EndGame();

	void PauseGame();

private:
	bool isGameOver;

	BC::Button* localToMenuButton;

	//ValidationManager reference
	ValidationManager& validationManager;
	//ScoreManager reference
	ScoreManager& scoreManager;
	//Score value
	int score;
};

