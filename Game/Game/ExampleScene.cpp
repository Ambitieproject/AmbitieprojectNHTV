#include "ExampleScene.h"
#include "SceneManager.h"



ExampleScene::ExampleScene(std::string sceneName) : Scene(sceneName) {

}


ExampleScene::~ExampleScene()
{
}

void ExampleScene::Start() {
	Scene::Start();

	std::cout << "Example scene 1 start function runnning" << std::endl;

	Scene& scene2 = SceneManager::GetSceneByIndex(2);

	std::cout << scene2.Name << std::endl;
}

void ExampleScene::Update(float deltaTime) {
	Scene::Update(deltaTime);
}
