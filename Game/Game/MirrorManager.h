#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <map>
#include <cmath>

//Include Audio manage accessibility
#include "AudioManager.h"

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"
#include "GameObject.h"
#include "BaseComponents.hpp"
#include "Equations.h"

#include "Mirror.h"
#include "ReflectorBeamManager.h"

#include <math.h>

//Manager for the mirrors
class MirrorManager : public Component {
public:
	//Constructor
	MirrorManager(BC::Button* addMirrorButton, ReflectorBeamManager* reflectorBeamManager);
	//Destructor
	~MirrorManager();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

	//Adds a mirror
	Mirror& AddMirror(sf::Vector2f position, float rotation);
	//Removes a mirror
	void DestroyMirror(GameObject& mirror);

	//Returns if a mirror is being moved
	bool IsMovingAMirror();

	//Gets the mirror map
	std::map<int, GameObject*>& GetMirrors();
	//Gets the current active mirror
	GameObject* GetCurrentMirror();

private:
	//Get the closest mirror to a beam
	GameObject* GetClosestMirrorForBeam(ReflectorBeam& beam);

	//Gets the closest hit location inside the closest mirror to a beam
	std::string GetClosestHitLocationInClosestMirrorForBeam(ReflectorBeam& beam, GameObject& closestMirror);
	//Gets a hit point by a specified side
	sf::Vector2f GetSideHitpointInClosestMirrorForBeamByName(std::string sideName, ReflectorBeam& beam, GameObject& closestMirror);

	//Gets the angle between a mirror and a beam
	float GetAngleBetweenMirrorAndIncomingBeam(ReflectorBeam& beam, GameObject& closestMirror);
	//Gets the rotation for a new beam that spawns out of a mirror
	float GetRotationForNewBeam(ReflectorBeam& beam, GameObject& closestMirror, float angleBetweenBeamAndMirror);

private:
	//Local current mirror
	GameObject* currentMirror;

	//Map of mirrors
	std::map<int, GameObject*> mirrors;
	//Index of map with mirrors
	int mirrorIndex;

	//Local add mirror button pointer
	BC::Button* localAddMirrorButton;

	//ReflectorBeamManager pointer
	ReflectorBeamManager* reflectorBeamManager = nullptr;
};
