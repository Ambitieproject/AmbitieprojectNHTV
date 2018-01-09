#pragma once

#include <iostream>
#include <limits>
#include <math.h>

#include "BaseComponents.hpp"
#include "Component.h"

#include "Equations.h"

class MirrorManager;
class ReflectorBeamManager;

class ReflectorBeam : public Component {
public:
	ReflectorBeam(ReflectorBeamManager* reflectorBeamManager, int beamIndexInMap, int beamRotation);
	~ReflectorBeam();

	void Start();
	void Update(float deltaTime);

	void DestroyNewLaser();

	sf::Vertex* GetLine();

	void SetLineColor(sf::Color color);

	sf::Vector2f GetDirection();
	int GetBeamIndexInMap();

	float beamRotation;

public:
	GameObject* mirrorSpawningFrom = nullptr;
	GameObject* reflectingMirror = nullptr;
	GameObject* newBeam = nullptr;

	
	bool isReflecting;

private:
	//Line in Vertexes
	sf::Vertex* line = new sf::Vertex[2];

	float slope;

	bool isCollidingWithMirror;

	int beamIndexInMap;

	//ReflectorBeamManager reference
	ReflectorBeamManager* reflectorBeamManager;
};

