#pragma once

#include <iostream>
#include <string>
#include <vector>

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

	GameObject testObject = GameObject("TestObject", *this);
	BC::Sprite prisma = BC::Sprite("../Assets/prisma.jpg");

	std::vector<sf::Color> prismaColors;

	int currentPrismaColorIndex;
	sf::Color currentPrismaColor;
};
