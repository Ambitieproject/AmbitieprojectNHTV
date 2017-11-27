#include "MirrorManager.h"
#include "GameObject.h"



MirrorManager::MirrorManager() {
	
}


MirrorManager::~MirrorManager()
{
}

void MirrorManager::Start() {
	Component::Start();

	isMovingAMirror = false;

	Mirror* mirror = new Mirror();
	AddMirror(mirror);
	mirror->mirrorSprite.setOrigin(mirror->mirrorSprite.GetTexture().getSize().x / 2, mirror->mirrorSprite.GetTexture().getSize().y / 2);
}

void MirrorManager::Update(float deltaTime) {
	Component::Update(deltaTime);

	//Get the mouse position
	const sf::Vector2f mousePos = sf::Vector2f(Input::GetMousePosition().x, Input::GetMousePosition().y);

	for (auto it = mirrors.begin(); it != mirrors.end(); it++) {
		if (it->second->mirrorBoxCollider.OnMouseDown(sf::Mouse::Button::Left)) {

			if (Input::GetKeyDown(sf::Keyboard::E)) {
				it->second->mirrorSprite.rotate(50 * deltaTime);
			}
			if (Input::GetKeyDown(sf::Keyboard::Q)) {
				it->second->mirrorSprite.rotate(-50 * deltaTime);
			}
			
			isMovingAMirror = true;
			it->second->mirrorSprite.setPosition(mousePos);
		}
	}

	if (isMovingAMirror) {
		if (Input::GetMouseKeyUp(sf::Mouse::Button::Left)) {
			isMovingAMirror = false;
		}
	}
}

bool MirrorManager::IsMovingAMirror() {
	return isMovingAMirror;
}

void MirrorManager::AddMirror(Mirror* mirror) { 
	GameObject->AddComponent(&mirror->mirrorSprite);
	GameObject->AddComponent(&mirror->mirrorBoxCollider);

	mirrors.insert(std::pair<int, Mirror*>(mirrorIndex, mirror));
	mirrorIndex++;
}
