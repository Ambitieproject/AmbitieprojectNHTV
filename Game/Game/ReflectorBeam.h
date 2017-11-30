#pragma once

#include <iostream>

#include "BaseComponents.hpp"
#include "MirrorManager.h"

class MirrorManager;
class ReflectorBeamManager;

class ReflectorBeam {
public:
	ReflectorBeam(MirrorManager* mirrorManager, ReflectorBeamManager* reflectorBeamManager);
	~ReflectorBeam();

	void Update(float deltaTime);
	void Grow(float deltaTime);

	void SetGrowSpeed(float growSpeed);

	BC::Sprite& GetSprite();
	BC::BoxCollider& GetBoxCollider();
	std::vector<sf::Vector2f>& GetPositions();
	std::vector<sf::Vector2f> positions;
	float GetGrowSpeed();
	GameObject* GetBeamReflectMirror();

	bool IsReflecting();
	void SetReflecting(bool state);

public:
	GameObject* cantReflectMirror;

private:
	float growSpeed;

	BC::Sprite reflectorBeamSprite = BC::Sprite("../Assets/pixelWhite.png");
	BC::BoxCollider reflectorBeamBoxCollider = BC::BoxCollider(reflectorBeamSprite);
	
	MirrorManager* mirrorManager;
	ReflectorBeamManager* reflectorBeamManager;

	GameObject* beamReflectMirror;

	bool isReflecting;
	bool hasReflectingBeam;
};

