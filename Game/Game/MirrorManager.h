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
};

class MirrorManager : public Component
{
public:
	MirrorManager();
	~MirrorManager();

	void Start();
	void Update(float deltaTime);

	bool IsMovingAMirror();

	void AddMirror(Mirror* mirror);

private:
	std::map<int, Mirror*> mirrors;
	int mirrorIndex;

	bool isMovingAMirror;
};

