#pragma once

#include <iostream>
#include <limits>
#include <math.h>

#include "BaseComponents.hpp"
#include "MirrorManager.h"
#include "Component.h"

#define PI 3.14159265

class MirrorManager;
class ReflectorBeamManager;

class ReflectorBeam : public Component {
public:
	ReflectorBeam(MirrorManager* mirrorManager, ReflectorBeamManager* reflectorBeamManager, int beamIndexInMap);
	~ReflectorBeam();

	void Start();
	void Update(float deltaTime);

	sf::Vertex* GetLine();

	void SetLineColor(sf::Color color);

	sf::Vector2f GetDirection();
	int GetBeamIndexInMap();

private:
	void DestroyNewLaser();

private:
	//Line in Vertexes
	sf::Vertex* line = new sf::Vertex[2];

	float slope;

	bool isCollidingWithMirror;

	GameObject* newBeam = nullptr;
	GameObject* mirrorSpawningFrom = nullptr;
	GameObject* reflectingMirror = nullptr;
	
	int beamIndexInMap;

	//MirrorManager reference
	MirrorManager* mirrorManager;
	//ReflectorBeamManager reference
	ReflectorBeamManager* reflectorBeamManager;
};

