#include "Mirror.h"
#include "Window.h"

//Constructor
Mirror::Mirror() {
	//Set default values
	rotateSpeed = 100;
}

//Destructor
Mirror::~Mirror() {

}

//Override Start method from base Component class
void Mirror::Start() {
	Component::Start();

	
}

//Override Update method from base Component class
void Mirror::Update(float deltaTime) {
	Component::Update(deltaTime);

	//Get the mouse position
	const sf::Vector2f mousePos = sf::Vector2f(Input::GetMousePosition().x, Input::GetMousePosition().y);

	//Get sprite and boxCollider component
	BC::Sprite* sprite = gameObject->GetComponent<BC::Sprite>();
	BC::BoxCollider* boxCollider = gameObject->GetComponent<BC::BoxCollider>();

	if (Input::GetMouseKeyPressed(sf::Mouse::Button::Left)) {
		if (boxCollider->GetBoxCollider().getGlobalBounds().contains(mousePos)) {
			canMove = true;
		}
	}

	if (canMove) {
		//If mousekey is down
		if (Input::GetMouseKeyDown(sf::Mouse::Button::Left)) {
			//Rotate right with E button down
			if (Input::GetKeyDown(sf::Keyboard::E)) {
				sprite->rotate(rotateSpeed * deltaTime);
			}
			//Rotate left with Q button down
			if (Input::GetKeyDown(sf::Keyboard::Q)) {
				sprite->rotate(-rotateSpeed * deltaTime);
			}

			//Set position to the mouse position
			sprite->setPosition(mousePos);
		}

		//If the mouse key is up
		if (Input::GetMouseKeyUp(sf::Mouse::Button::Left)) {
			canMove = false;
		}
	}
}

//Get line
sf::Vertex* Mirror::GetLine() {
	return reflectLine;
}

//Get can move
bool Mirror::CanMove() {
	return canMove;
}
