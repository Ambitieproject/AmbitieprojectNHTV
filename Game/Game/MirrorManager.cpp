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
			currentMirror = it->second;
			it->second->mirrorSprite.setPosition(mousePos);
		}
		else {
			currentMirror = nullptr;
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

Mirror* MirrorManager::GetCurrentMirror() {
	return currentMirror;
}

void MirrorManager::AddMirror(Mirror* mirror) { 
	GameObject->AddComponent(&mirror->mirrorSprite);
	GameObject->AddComponent(&mirror->mirrorBoxCollider);

	mirrors.insert(std::pair<int, Mirror*>(mirrorIndex, mirror));
	mirrorIndex++;
}

void Mirror::GetPositionsInMirror(std::vector<sf::Vector2f>& positions) {

	float width = mirrorSprite.getTexture()->getSize().x * mirrorSprite.getScale().x;
	float height = mirrorSprite.getTexture()->getSize().y * mirrorSprite.getScale().y;

	float xMin = (mirrorSprite.getPosition().x - (width / 2));
	float xMax = (mirrorSprite.getPosition().x + (width / 2));

	float yMin = mirrorSprite.getPosition().y - (height / 2);
	float yMax = mirrorSprite.getPosition().y + (height / 2);

	std::cout << xMin << std::endl;
	std::cout << xMax << std::endl;
	std::cout << yMin << std::endl;
	std::cout << yMax << std::endl;

	for (auto it = positions.begin(); it != positions.end(); it++) {
		if (it->x >= xMin && it->x <= xMax && it->y >= yMin && it->y <= yMax) {
			std::cout << "true" << std::endl;
		}
	}
}
