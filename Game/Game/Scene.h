#pragma once

//#include "GameObject.h"
#include "Scene.h"
#include "GameObject.h"

#include <map>
#include <list>
#include <vector>

//Base scene class. A custom Scene class needs to be inherited from this class to be able to be a scene
class Scene
{
public:
	//Constructor
	Scene();
	//Destructor
	~Scene();

	//Virtual Start Method of a scene that can be overwritten in a supper class 
	virtual void Start();
	//Virtual Update Method of a scene that can be overwritten in a supper class
	virtual void Update(float deltaTime);

	//Adds a given GameObject to the list of GameObjects in the scene
	void AddToGameObjectList(GameObject* gameObject);

	//Finds a GameObject by name
	GameObject* FindGameObjectByName(std::string gameObjectName);

public:
	//Map of GameObjects in the scene
	std::map<int, GameObject*> GameObjects;

private:
	//Local index of GameObjects in the scene
	int gameObjectLayerIndex;
};
