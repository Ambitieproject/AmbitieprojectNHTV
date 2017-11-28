#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <map>
#include <vector>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"

#include "BaseComponents.hpp"
#include "MirrorManager.h"
#include "PrismaMovementController.h"

struct Beam {
	BC::Sprite beam = BC::Sprite("../Assets/pixelWhite.png");
	BC::BoxCollider beamBoxCollider = BC::BoxCollider(beam);
	std::vector<sf::Vector2f> positions;
};

class ReflectorBeam : public Component {
public:
	ReflectorBeam(std::string beamFilePath);
	~ReflectorBeam();

	void Start();
	void Update(float deltaTime);

	
private:
	void AddBeam(Beam* beam);

	void SetBeamColor();

	void ResetBeam();

private:
	std::string beamFilePath;

	std::map<int, Beam*> beams;
	int beamIndex;

	BC::Sprite* prisma;
	MirrorManager* mirrorManager;
	PrismaMovementController* prismaMovementController;

	///Color handeling
	std::vector<sf::Color> prismaColors;

	int currentPrismaColorIndex;
	sf::Color currentPrismaColor;
};

