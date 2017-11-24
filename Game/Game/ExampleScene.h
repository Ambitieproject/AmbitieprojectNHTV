#pragma once

#include <iostream>
#include <string>

#include "Scene.h"
#include "BaseComponents.hpp"
#include "GameObject.h"

class ExampleScene : public Scene {
public:
	ExampleScene(std::string sceneName);
	~ExampleScene();

	void Awake();
	void Start();
	void Update(float deltaTime);

private:
	/*
	///Enemy stuff
	GameObject enemyGameObject = GameObject("trump", *this);
	BC::Sprite trump = BC::Sprite("../Assets/trump_run.png");
	BC::BoxCollider boxColliderTrump = BC::BoxCollider(trump);
	BC::Animator animator = BC::Animator();
	BC::AnimationClip forwardWalkAnim = BC::AnimationClip("backWalk", "../Assets/trump_run.png", sf::Vector2u(6, 4), 6, 0.1f, trump, 0);

	///Hero stuff
	GameObject heroGameObject = GameObject("hero", *this);
	BC::Sprite hero = BC::Sprite("../Assets/kel.png");
	BC::BoxCollider boxColliderHero = BC::BoxCollider(hero);

	///UI stuff
	GameObject UIGameObject = GameObject("UIManager", *this);
	BC::Button testButton = BC::Button("../Assets/buttonNormal.png", "../Assets/buttonHovered.png", "../Assets/buttonPressed.png");
	*/

	GameObject testObject = GameObject("TestObject", *this);
	BC::Sprite prisma = BC::Sprite("../Assets/prisma.jpg");
};
