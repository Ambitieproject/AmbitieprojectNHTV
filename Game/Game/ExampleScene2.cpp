#include "ExampleScene2.h"



ExampleScene2::ExampleScene2(std::string sceneName) : Scene(sceneName) {

}


ExampleScene2::~ExampleScene2()
{
}

void ExampleScene2::Start() {
	Scene::Start();

	std::cout << "Example scene 2 start function runnning" << std::endl;
}

void ExampleScene2::Update(float deltaTime) {
	Scene::Update(deltaTime);
}
