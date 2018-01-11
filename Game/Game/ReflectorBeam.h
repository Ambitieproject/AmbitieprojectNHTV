#pragma once

#include <iostream>
#include <limits>
#include <math.h>

//Include all engine header files
#include "BaseComponents.hpp"
#include "Component.h"
#include "Equations.h"

//Forward include managers
class MirrorManager;
class ReflectorBeamManager;

//ReflectorBeam component class
class ReflectorBeam : public Component {
public:
	//Constructor
	ReflectorBeam(ReflectorBeamManager* reflectorBeamManager, int beamIndexInMap, int beamRotation);
	//Destructor
	~ReflectorBeam();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

	//Destroys laser
	void DestroyNewLaser();

	//Set laser line color
	void SetLineColor(sf::Color color);

	//Set direction
	sf::Vector2f SetDirection(sf::Vector2f direction);

	//Get the laser line
	sf::Vertex* GetLine();
	//Get direction vector
	sf::Vector2f GetDirection();

	//Get beam index in map
	int GetBeamIndexInMap();


public:
	//Beam rotation value
	float BeamRotation;

	//Not rotated beam bool
	bool NoRotationBeam;

	//The Mirror the beam is spawning from 
	GameObject* mirrorSpawningFrom = nullptr;
	//The mirror the beam is reflecting against
	GameObject* reflectingMirror = nullptr;

	//New beam object
	GameObject* newBeam = nullptr;

private:
	//Line in Vertexes
	sf::Vertex* line = new sf::Vertex[2];

	//Direction vector
	sf::Vector2f direction;

	//slope value of this laser
	float slope;

	//Beam index in map
	int beamIndexInMap;

	//ReflectorBeamManager reference
	ReflectorBeamManager* reflectorBeamManager;
};

