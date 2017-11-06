#pragma once

#include "Scene.h"

class ExampleScene : public Scene {
public:
	ExampleScene(std::string sceneName);
	~ExampleScene();

	void Start();
	void Update(float deltaTime);
};

