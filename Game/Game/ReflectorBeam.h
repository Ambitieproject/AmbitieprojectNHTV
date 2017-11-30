#pragma once

#include <iostream>

#include "BaseComponents.hpp"
#include "MirrorManager.h"

class ReflectorBeam {
public:
	ReflectorBeam(MirrorManager* mirrorManager);
	~ReflectorBeam();

	void Update(float deltaTime);
	void Grow(float deltaTime);

	void SetGrowSpeed(float growSpeed);

	BC::Sprite& GetSprite();
	BC::BoxCollider& GetBoxCollider();
	std::vector<sf::Vector2f>& GetPositions();
	std::vector<sf::Vector2f> positions;
	float GetGrowSpeed();

	bool IsReflecting();
	void SetReflecting(bool state);

private:
	float growSpeed;

	BC::Sprite reflectorBeamSprite = BC::Sprite("../Assets/pixelWhite.png");
	BC::BoxCollider reflectorBeamBoxCollider = BC::BoxCollider(reflectorBeamSprite);
	
	
	MirrorManager* mirrorManager;

	bool isReflecting;
	bool hasReflectingBeam;
};

