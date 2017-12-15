#pragma once

#include <iostream>
#include <string>
#include <map>
#include <SFML\Graphics.hpp>

#include "Window.h"
#include "Input.h"
#include "SceneManager.h"

#include "GameObject.h"

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

	//Makes a GameObject into a singleton
	GameObject& AddSingleton(GameObject& gameObject);
	//Gets an already made singleton GameObject
	GameObject* GetSingleton(std::string gameObjectName);
	//Gets all the singletons
	std::map<int, GameObject*> GetSingletons();

	//Gets Window class method
	Window& GetWindowClass();
	//Gets SceneManager method
	SceneManager& GetSceneManager();

public:
	//Main delta time for the whole game to access
	float DeltaTime;

private:
	//Private clock to get a delta time
	sf::Clock clock;

	//Vector containing Singleton GameObjects
	std::map<int, GameObject*> singletons;
	int singletonIndex;

	///main components
	Window* window;
	SceneManager* sceneManager;
	//The Input component is a static class
};