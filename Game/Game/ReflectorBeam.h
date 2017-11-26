#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"

#include "BaseComponents.hpp"

class ReflectorBeam : public Component {
public:
	ReflectorBeam(std::string beamFilePath);
	~ReflectorBeam();

	std::string beamFilePath;
	BC::Sprite* beam;

	void Awake();
	void Update(float deltaTime);
};

