#include "MirrorManager.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Window.h"

MirrorManager::MirrorManager() {
	
}


MirrorManager::~MirrorManager()
{
}

void MirrorManager::Start() {
	Component::Start();

	isMovingAMirror = false;

	AddMirror();
	AddMirror();
}

void MirrorManager::Update(float deltaTime) {
	Component::Update(deltaTime);

	//Get the mouse position
	const sf::Vector2f mousePos = sf::Vector2f(Input::GetMousePosition().x, Input::GetMousePosition().y);

	for (auto it = mirrors.begin(); it != mirrors.end(); it++) {
		BC::Sprite* sprite = it->second->GetComponent<BC::Sprite>();
		BC::BoxCollider* boxCollider = it->second->GetComponent<BC::BoxCollider>();
		Mirror* mirror = it->second->GetComponent<Mirror>();

		if (boxCollider->OnMouseEnter()) {
			if (!currentMirror) {
				mirror->canMove = true;
			}
			
		}
		if (boxCollider->OnMouseExit()) {
			mirror->canMove = false;
		}

		if (mirror->canMove) {
			if (Input::GetMouseKeyDown(sf::Mouse::Button::Left)) {
				if (Input::GetKeyDown(sf::Keyboard::E)) {
					sprite->rotate(50 * deltaTime);
				}
				if (Input::GetKeyDown(sf::Keyboard::Q)) {
					sprite->rotate(-50 * deltaTime);
				}

				isMovingAMirror = true;
				currentMirror = it->second;
				sprite->setPosition(mousePos);
			}
			if (Input::GetMouseKeyUp(sf::Mouse::Button::Left)) {
				mirror->canMove = false;
			}
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

GameObject* MirrorManager::GetCurrentMirror() {
	return currentMirror;
}

void MirrorManager::AddMirror() { 
	//Make mirror GameObject and Components
	GameObject* mirror = new GameObject("Mirror", gameObject->GetScene());
	Mirror* mirrorComponent = new Mirror();
	BC::Sprite* mirrorSprite = new BC::Sprite("../Assets/Mirror.png");
	BC::BoxCollider* mirrorBoxCollider = new BC::BoxCollider(*mirrorSprite);

	//Add components to GameObject
	mirror->AddComponent(mirrorComponent);
	mirror->AddComponent(mirrorSprite);
	mirror->AddComponent(mirrorBoxCollider);

	//Add GameObject to scene
	gameObject->GetScene().AddToGameObjectList(mirror);

	//Set origin of mirror sprite to be in the middle
	mirrorSprite->setOrigin(mirrorSprite->GetTexture().getSize().x / 2, mirrorSprite->GetTexture().getSize().y / 2);
	//Set position to be random across the window width size
	mirrorSprite->setPosition(sf::Vector2f(rand() % ((Window::GetInstance()->GetWindowSize().x - 40) - 40 + 1) + 40, 20));
	
	//Add mirror to the mirror list and increment the index of that list
	mirrors.insert(std::pair<int, GameObject*>(mirrorIndex, mirror));
	mirrorIndex++;
}

int MirrorManager::GetPositionsInMirror(sf::Sprite* sprite, std::vector<sf::Vector2f>& positions) {

	float width = sprite->getTexture()->getSize().x * sprite->getScale().x;
	float height = sprite->getTexture()->getSize().y * sprite->getScale().y;

	float xMin = sprite->getPosition().x - (width / 2);
	float xMax = sprite->getPosition().x + (width / 2);

	float yMin = sprite->getPosition().y - (height / 2);
	float yMax = sprite->getPosition().y + (height / 2);

	int count = 0;

	for (auto it = positions.begin(); it != positions.end(); it++) {
		if (it->x >= xMin && it->x <= xMax && it->y >= yMin && it->y <= yMax) {
			while (it != positions.end()) {
				count++;
				it = positions.erase(it);
			}
			return count;
		}
	}
	return 0;
}
