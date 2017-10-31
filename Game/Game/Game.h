#pragma once

#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>

#include "RenderWindow.h"
#include "InputManager.h"

//Main Game class which is the upper class of all classes in this framework
class Game {

#pragma region Singleton
private:
	//Private static instance of class
	static Game* instance;

	//Private constructor to prevent instancing
	Game();

public:
	//Static Get Method
	static Game* GetInstance();
#pragma endregion

public:
	//Destructor
	~Game();

	//Main Start method that runs in the whole game
	void Start();
	//Main Update method that runs in the whole game
	void Update();

	//Gets Window class method
	RenderWindow& GetWindowClass();
	//Gets SceneManager method
	//SceneManager* GetSceneManager();
	//Gets InputManager Method
	InputManager& GetInputManager();

public:
	//Main delta time  for the whole game to access
	float DeltaTime;

private:
	//Private clock to get a delta time
	sf::Clock clock;

	///main components
	RenderWindow window;
	//SceneManager sceneManager = SceneManager(this);
	InputManager input;
};