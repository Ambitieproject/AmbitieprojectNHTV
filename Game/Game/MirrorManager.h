#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <map>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"

#include "GameObject.h"

#include "BaseComponents.hpp"

class MirrorManager : public Component
{
public:
	MirrorManager();
	~MirrorManager();

	void Start();
	void Update(float deltaTime);

	bool IsMovingAMirror();

	std::map<int, GameObject*>& GetMirrors();
	GameObject* GetCurrentMirror();

	void AddMirror();

private:
	GameObject* currentMirror;

	std::map<int, GameObject*> mirrors;
	int mirrorIndex;

	bool isMovingAMirror;
};

class Mirror : public Component {
public:
	bool canMove;
	sf::Vector2f pointOfIntersect;

	sf::Vertex* GetLine();
	float GetSlope();

	sf::Vertex* reflectLine = new sf::Vertex[2];
	std::vector<sf::Vertex*> ignoreLines;

	void DrawMirrorLine();
};

