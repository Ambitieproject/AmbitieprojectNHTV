#include "ExampleScene.h"
#include "SceneManager.h"
#include "Input.h"



ExampleScene::ExampleScene(std::string sceneName) : Scene(sceneName) {

}


ExampleScene::~ExampleScene()
{
}

void ExampleScene::Start() {
	Scene::Start();

	std::cout << "Example scene 1 start function runnning" << std::endl;

	Input::CreateAxis("MovementX", sf::Keyboard::Key::D, sf::Keyboard::Key::A);
	Input::CreateAxis("MovementY", sf::Keyboard::Key::W, sf::Keyboard::Key::S);

	Input::ChangeAxis("MovementX", ChangeKey::Both, sf::Keyboard::Right, sf::Keyboard::Left);
}

void ExampleScene::Update(float deltaTime) {
	Scene::Update(deltaTime);

	float movX = Input::GetAxis("MovementX");
	float movY = Input::GetAxis("MovementY");

	std::cout << movX << std::endl;
	std::cout << movY << std::endl;
}
