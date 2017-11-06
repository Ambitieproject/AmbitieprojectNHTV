#pragma once
#include <iostream>
#include <map>

#include "Scene.h"

//Forward include the same hierachy class Window
class Renderer;

//all scenes includes
#include "ExampleScene.h"
#include "ExampleScene2.h"

//SceneManager class. Takes care of the scene flow of the game and calls different methods of the "active" scene
class SceneManager {

#pragma region Singleton
private:
	//Private static instance of class
	static SceneManager* instance;

	//Private constructor to prevent instancing
	SceneManager();

	//Static Get Method
	static SceneManager* GetInstance();
#pragma endregion

public:
	//Load a scene specified by a scene index
	static bool LoadScene(int sceneIndex);
	//Load a scene specified by a scene name
	static bool LoadScene(std::string sceneName);

	//Gets a scene by the index specified as a parameter
	static Scene& GetSceneByIndex(int sceneIndex);
	//Gets a scene by a name specified as a parameter
	static Scene& GetSceneByName(std::string sceneName);

private:
	//Destructor
	~SceneManager();

	//Adds scene to list of scenes
	static void AddSceneToSceneManager(Scene* scene);

	void StartSceneManager();

	//Method that updates the current active scene
	void UpdateCurrentScene(float deltaTime);
	//Method that renders the current active scene
	void RenderCurrentScene();

private:
	//Define the friend class Game
	friend class Game;
	//Define the friend class Scene
	friend class Scene;

	//Pointer to the renderer class
	Renderer* renderer;

	//Map with all the scenes available in the game
	static std::map<int, Scene*> scenes;
	//Index that holds the amount of Scenes in the game
	static int sceneIndexAmount;

	//Pointer that holds the current active scene
	static Scene* currentScene;

	///all scenes in game
	ExampleScene exampleScene = ExampleScene("ExampleScene");
	ExampleScene2 exampleScene2 = ExampleScene2("ExampleScene2");
};

