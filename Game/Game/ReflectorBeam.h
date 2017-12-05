#pragma once

#include <iostream>

#include "BaseComponents.hpp"
#include "MirrorManager.h"
#include "Component.h"

class MirrorManager;
class ReflectorBeamManager;

class ReflectorBeam : public Component {
public:
	ReflectorBeam(MirrorManager* mirrorManager, ReflectorBeamManager* reflectorBeamManager);
	~ReflectorBeam();

	void Update(float deltaTime);

	sf::Vertex* GetLine();

	void SetLineColor(sf::Color color);

private:
	sf::Vertex* line = new sf::Vertex[2];

	//MirrorManager reference
	MirrorManager* mirrorManager;
	//ReflectorBeamManager reference
	ReflectorBeamManager* reflectorBeamManager;
};

