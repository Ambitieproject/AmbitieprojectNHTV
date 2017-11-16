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
	GameObject gameObject1 = GameObject("TextObject", *this);

	BC::Sprite trump = BC::Sprite("../Assets/trump_run.png", false);
	BC::Sprite hero = BC::Sprite("../Assets/kel.png", false);

	BC::Animator animator = BC::Animator();
	bool setAnims = false;

	BC::AnimationClip forwardWalkAnim = BC::AnimationClip("backWalk", "../Assets/trump_run.png", sf::Vector2u(6, 4), 6, 0.1f, trump.GetSprite(), 0);
	BC::AnimationClip backWalkAnim = BC::AnimationClip("forwardWalk", "../Assets/trump_run.png", sf::Vector2u(6, 4), 6, 0.1f, trump.GetSprite(), 2);
	BC::AnimationClip rightWalkAnim = BC::AnimationClip("rightWalk", "../Assets/trump_run.png", sf::Vector2u(6, 4), 6, 0.1f, trump.GetSprite(), 1);
	BC::AnimationClip leftWalkAnim = BC::AnimationClip("leftWalk", "../Assets/trump_run.png", sf::Vector2u(6, 4), 6, 0.1f, trump.GetSprite(), 3);
};
