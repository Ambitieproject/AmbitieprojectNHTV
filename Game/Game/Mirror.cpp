#include "Mirror.h"
#include "MirrorManager.h"

//Constructor
Mirror::Mirror(MirrorManager* mirrorManager) : mirrorManager(mirrorManager) {
	//Set default values
	rotateSpeed = 100;
	isMoving = false;
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

}

//Moves the mirror
void Mirror::Move(float deltaTime) {
	//Get the mouse position
	const sf::Vector2f mousePos = sf::Vector2f(Input::GetMousePosition().x, Input::GetMousePosition().y);
	
	//Get sprite and boxCollider component
	BC::Sprite* sprite = gameObject->GetComponent<BC::Sprite>();
	BC::BoxCollider* boxCollider = gameObject->GetComponent<BC::BoxCollider>();

	//If mouse is in mirror and button is pressed then set is moving
	if (boxCollider->GetBoxCollider().getGlobalBounds().contains(mousePos)) {
		if (Input::GetMouseKeyPressed(sf::Mouse::Button::Left)) {
			//Set is moving
			isMoving = true;
		}
	}

	if (isMoving) {
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

			//If right mouse is pressed while dragging then delete mirror object
			if (Input::GetMouseKeyDown(sf::Mouse::Button::Right)) {
				mirrorManager->DestroyMirror(*gameObject);
			}
		}
	}

	//If the mouse key is up
	if (Input::GetMouseKeyUp(sf::Mouse::Button::Left) && isMoving) {
		isMoving = false;
	}
}

//Get line
sf::Vertex* Mirror::GetLine() {
	return reflectLine;
}

void Mirror::SetMoving(bool moveState) {
	isMoving = moveState;
}

//Get the state of this mirror being moved
bool Mirror::IsMoving() {
	return isMoving;
}

//Get the state of the object being a static object
bool Mirror::IsStaticObject() {
	return isStaticObject;
}

//Set the state of the object being a static object
void Mirror::SetIsStaticObject(bool isStatic) {
	isStaticObject = isStatic;

	//If the object is static,
	//Change its texture
	if (isStaticObject) {
		sf::Texture* texture = &gameObject->GetComponent<BC::Sprite>()->GetTexture();
		texture->loadFromFile("../Assets/Art/Level/NoMoveMirror.png");
		gameObject->GetComponent<BC::Sprite>()->setTexture(*texture);
	}
}
