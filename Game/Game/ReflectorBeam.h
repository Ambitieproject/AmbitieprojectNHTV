#pragma once

#include <iostream>
#include <limits>
#include <math.h>

#include "BaseComponents.hpp"
#include "Component.h"

#define PI 3.14159265

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

public:
	GameObject* mirrorSpawningFrom = nullptr;
	GameObject* reflectingMirror = nullptr;
	GameObject* newBeam = nullptr;

	float beamRotation;
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

