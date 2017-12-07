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
}

void MirrorManager::Update(float deltaTime) {
	Component::Update(deltaTime);

	//Get the mouse position
	const sf::Vector2f mousePos = sf::Vector2f(Input::GetMousePosition().x, Input::GetMousePosition().y);

	for (auto it = mirrors.begin(); it != mirrors.end(); it++) {
		BC::Sprite* sprite = it->second->GetComponent<BC::Sprite>();
		BC::BoxCollider* boxCollider = it->second->GetComponent<BC::BoxCollider>();
		Mirror* mirror = it->second->GetComponent<Mirror>();

		if (boxCollider->GetBoxCollider().getGlobalBounds().contains(mousePos)) {
			if (!currentMirror) {
				mirror->canMove = true;
			}
		}
		else {
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

std::map<int, GameObject*>& MirrorManager::GetMirrors() {
	return mirrors;
}

GameObject* MirrorManager::GetCurrentMirror() {
	return currentMirror;
}

void MirrorManager::AddMirror() { 
	//Make mirror GameObject and Components
	GameObject* mirror = new GameObject("Mirror", gameObject->GetScene());
	mirror->SetDrawIndex(3);
	Mirror* mirrorComponent = new Mirror();
	BC::Sprite* mirrorSprite = new BC::Sprite("../Assets/Mirror.png");
	BC::BoxCollider* mirrorBoxCollider = new BC::BoxCollider(*mirrorSprite);

	//Add components to GameObject
	mirror->AddComponent(mirrorComponent);
	mirror->AddComponent(mirrorSprite);
	mirror->AddComponent(mirrorBoxCollider);

	mirrorSprite->rotate(225);

	//Add GameObject to scene
	gameObject->GetScene().AddToGameObjectList(mirror);

	//Set origin of mirror sprite to be in the middle
	mirrorSprite->setOrigin(mirrorSprite->GetTexture().getSize().x / 2, mirrorSprite->GetTexture().getSize().y / 2);
	//Set position to be random across the window width size
	mirrorSprite->setPosition(sf::Vector2f(rand() % ((Window::GetInstance()->GetWindowSize().x - 40) - 40 + 1) + 40, rand() % (200 - 100 + 1) + 100));
	
	//Add mirror to the mirror list and increment the index of that list
	mirrors.insert(std::pair<int, GameObject*>(mirrorIndex, mirror));
	mirrorIndex++;
}

sf::Vertex* Mirror::GetLine() {
	if (line != nullptr) {
		return line;
	}
	else {
		return nullptr;
	}
}

float Mirror::GetSlope() {
	if (line != nullptr) {
		float y = line[0].position.y - line[1].position.y;
		float x = line[0].position.x - line[1].position.x;
		return y / x;
	}
	return 0;
}

void Mirror::DrawMirrorLine() {
	if (line != nullptr) {
		BC::BoxCollider* thisCollider = gameObject->GetComponent<BC::BoxCollider>();

		sf::Vector2f leftBottomPoint = thisCollider->GetBoxCollider().getTransform().transformPoint(thisCollider->GetBoxCollider().getPoint(0));
		sf::Vector2f rightBottomPoint = thisCollider->GetBoxCollider().getTransform().transformPoint(thisCollider->GetBoxCollider().getPoint(1));

		//std::cout << leftBottomPoint.x << " " << leftBottomPoint.y << std::endl;
		//std::cout << rightBottomPoint.x << " " << rightBottomPoint.y << std::endl;

		line = new sf::Vertex[2];
		line[0].position = leftBottomPoint;
		line[0].color = sf::Color::Blue;
		line[1].position = rightBottomPoint;
		line[1].color = sf::Color::Red;
	}
	else {
		Window::GetInstance()->GetRenderer().Draw(line, 2, sf::Lines);
	}
}
