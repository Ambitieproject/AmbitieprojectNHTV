#include "MirrorManager.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Window.h"

//Constructor
MirrorManager::MirrorManager() {
	
}

//Destructor
MirrorManager::~MirrorManager() {

}

//Override Start method from base Component class
void MirrorManager::Start() {
	Component::Start();
}

//Override Update method from base Component class
void MirrorManager::Update(float deltaTime) {
	Component::Update(deltaTime);
}

//Adds a mirror
void MirrorManager::AddMirror() {
	//Make mirror GameObject
	GameObject* mirror = new GameObject("Mirror", gameObject->GetScene());

	//Set mirror draw index
	mirror->SetDrawIndex(3);

	//Make components
	Mirror* mirrorComponent = new Mirror();
	BC::Sprite* mirrorSprite = new BC::Sprite("../Assets/Mirror2.png");
	BC::BoxCollider* mirrorBoxCollider = new BC::BoxCollider(*mirrorSprite);

	//Add components to GameObject
	mirror->AddComponent(mirrorComponent);
	mirror->AddComponent(mirrorSprite);
	mirror->AddComponent(mirrorBoxCollider);

	//Set a rotation of the mirror
	mirrorSprite->rotate(225);

	//Set origin of mirror sprite to be in the middle
	mirrorSprite->setOrigin(mirrorSprite->GetTexture().getSize().x / 2, mirrorSprite->GetTexture().getSize().y / 2);
	//Set position to be random across the window width size
	mirrorSprite->setPosition(sf::Vector2f(rand() % ((Window::GetInstance()->GetWindowSize().x - 40) - 40 + 1) + 40, rand() % (200 - 100 + 1) + 100));

	//Add mirror to the mirror list and increment the index of that list
	mirrors.insert(std::pair<int, GameObject*>(mirrorIndex, mirror));
	mirrorIndex++;
}

//Returns if a mirror is being moved
bool MirrorManager::IsMovingAMirror() {
	//Go through all the mirrors, if one is moving return true
	for (auto it = mirrors.begin(); it != mirrors.end(); it++) {
		if (it->second->GetComponent<Mirror>()->CanMove()) {
			return true;
		}
	}
	//If no mirror is moving return false
	return false;
}

//Gets the mirror map
std::map<int, GameObject*>& MirrorManager::GetMirrors() {
	return mirrors;
}

//Gets the current active mirror
GameObject* MirrorManager::GetCurrentMirror() {
	return currentMirror;
}
