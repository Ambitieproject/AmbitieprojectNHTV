#pragma once

#include "Scene.h"

class ExampleScene2 : public Scene {
public:
	ExampleScene2(std::string sceneName);
	~ExampleScene2();

	void Start();
	void Update(float deltaTime);
};

