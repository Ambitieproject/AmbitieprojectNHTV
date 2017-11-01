#pragma once
#include <iostream>
#include <map>

#include "Scene.h"

//Forward include the same hierachy class Window
class Window;

//all scenes includes
//#include "MainScene.h"

//SceneManager class. Takes care of the scene flow of the game and calls different methods of the "active" scene
class SceneManager
{
public:
	//Constructor
	SceneManager();
	//Destructor
	~SceneManager();

	//Sets references for the SceneManager to communicate
	void Setup();

	//Method that start the current active scene
	void StartCurrentScene();
	//Method that updates the current active scene
	void UpdateCurrentScene(float deltaTime);
	//Method that renders the current active scene
	void RenderCurrentScene();

private:
	//Pointer to the window class
	Window* window;

	//Map with all the scenes available in the game
	std::map<int, Scene*> scenes;

	//Pointer that holds the current active scene
	Scene* currentScene;

	///all scenes in game
	//MainScene mainScene;
};

