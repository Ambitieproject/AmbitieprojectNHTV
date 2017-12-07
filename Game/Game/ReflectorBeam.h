#pragma once

#include <iostream>
#include <limits>
#include <math.h>

#include "BaseComponents.hpp"
#include "MirrorManager.h"
#include "Component.h"

class MirrorManager;
class ReflectorBeamManager;

class ReflectorBeam : public Component {
public:
	ReflectorBeam(MirrorManager* mirrorManager, ReflectorBeamManager* reflectorBeamManager);
	~ReflectorBeam();

	void Start();
	void Update(float deltaTime);

	sf::Vertex* GetLine();

	void SetLineColor(sf::Color color);

	sf::Vector2f GetDirection();

private:
	//Line in Vertexes
	sf::Vertex* line = new sf::Vertex[2];

	float slope;

	bool isCollidingWithMirror;

	GameObject* mirrorSpawningFrom = nullptr;

	//MirrorManager reference
	MirrorManager* mirrorManager;
	//ReflectorBeamManager reference
	ReflectorBeamManager* reflectorBeamManager;
};

