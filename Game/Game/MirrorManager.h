#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <map>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"

#include "BaseComponents.hpp"

struct Mirror {
	BC::Sprite mirrorSprite = BC::Sprite("../Assets/Mirror.png");
	BC::BoxCollider mirrorBoxCollider = BC::BoxCollider(mirrorSprite);
	void GetPositionsInMirror(std::vector<sf::Vector2f>& positions);
};

class MirrorManager : public Component
{
public:
	MirrorManager();
	~MirrorManager();

	void Start();
	void Update(float deltaTime);

	bool IsMovingAMirror();
	Mirror* GetCurrentMirror();

	void AddMirror(Mirror* mirror);

private:
	Mirror* currentMirror;

	std::map<int, Mirror*> mirrors;
	int mirrorIndex;

	bool isMovingAMirror;
};

