#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <map>
#include <vector>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"

#include "BaseComponents.hpp"
#include "MirrorManager.h"
#include "ReflectorBeam.h"

//Manager class that takes care of managing the reflector beams
class ReflectorBeamManager : public Component {
public:
	//Constructor
	ReflectorBeamManager();
	//Destructor
	~ReflectorBeamManager();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

	//Adds a beam with a position
	GameObject& AddBeam(sf::Vector2f position, int rotation, sf::Color color);

	//Destroy a beam
	void DestroyBeam(GameObject* beam);

	//Gets the beams map
	std::map<int, GameObject*>& GetBeams();

private:

	std::map<int, GameObject*> beams;
	int beamIndex;

	//Prisma reference
	BC::Sprite* prisma;
	//MirrorManager reference
	MirrorManager* mirrorManager;
};

