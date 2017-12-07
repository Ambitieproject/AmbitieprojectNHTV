#include "ShapeAssignmentManager.h"
#include "GameObject.h"
#include "Window.h"
#include "HelperMethods.h"

//Constructor
ShapeAssignmentManager::ShapeAssignmentManager() {
}

//Destructor
ShapeAssignmentManager::~ShapeAssignmentManager() {

}

//Override Start method from base Component class
void ShapeAssignmentManager::Start() {
	Component::Start();

	shapeAssignmentText = gameObject->GetComponent<BC::Text>();
	SetNewShapeAssignment(ShapeAssignment::Triangle);
	DisplayAssignment();
}

//Override Update method from base Component class
void ShapeAssignmentManager::Update(float deltaTime) {
	Component::Update(deltaTime);

	if (Input::GetAnyKeyReleased()) {
		SetNewShapeAssignment(ShapeAssignment::Parrallelogram);
		std::cout << HelperMethods::GetRandomInt(0, 5) << std::endl;
		DisplayAssignment();
	}
}

//Sets a new shape assignment
ShapeAssignment& ShapeAssignmentManager::SetNewShapeAssignment(ShapeAssignment newShapeAssignment) {
	shapeAssignment = newShapeAssignment;
	return shapeAssignment;
}

//Displays the assignment as text
void ShapeAssignmentManager::DisplayAssignment() {
	std::string textContent;

	switch (shapeAssignment) {
	case ShapeAssignment::Parrallelogram:
		textContent = "Parrallelogram";
		break;
	case ShapeAssignment::Rectangle:
		textContent = "Rectangle";
		break;
	case ShapeAssignment::Square:
		textContent = "Square";
		break;
	case ShapeAssignment::Trapezoid:
		textContent = "Trapezoid";
		break;
	case ShapeAssignment::Triangle:
		textContent = "Triangle";
		break;
	}

	shapeAssignmentText->setString(textContent);

	sf::FloatRect bounds = shapeAssignmentText->getGlobalBounds();
	shapeAssignmentText->setPosition((Window::GetInstance()->GetWindowSize().x / 2) - (bounds.width / 2), Window::GetInstance()->GetWindowSize().y - 50);
}
