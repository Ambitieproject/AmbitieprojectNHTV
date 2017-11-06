#pragma once

#include "GameObject.h"
#include "Scene.h"
#include "GameObject.h"

//Forward include the upper class hierachy class SceneManager
class SceneManager;

#include <map>
#include <list>
#include <vector>

//Base scene class. A custom Scene class needs to be inherited from this class to be able to be a scene
class Scene
{
public:
	//Constructor
	Scene(std::string sceneName);
	//Destructor
	~Scene();

	//Initialization method that runs all the nessesary code to setup a scene
	void Init();

	//Virtual Start Method of a scene that can be overwritten in a supper class 
	virtual void Start();
	//Virtual Update Method of a scene that can be overwritten in a supper class
	virtual void Update(float deltaTime);
	//Virutal Quit Method of a scene that can be overwritten in a supper class
	virtual void Quit();

	//Adds a given GameObject to the list of GameObjects in the scene
	void AddToGameObjectList(GameObject* gameObject);

	//Finds a GameObject by name
	GameObject* FindGameObjectByName(std::string gameObjectName);

public:
	//Name of the scene
	std::string Name;

	//Scene index
	int SceneIndex;

	//Map of GameObjects in the scene
	std::map<int, GameObject*> GameObjects;

private:
	//Local index of GameObjects in the scene
	int gameObjectLayerIndex;

	//Local instance of the SceneManager
	SceneManager* sceneManager;
};
