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

	//Getting Component
	shapeAssignmentText = gameObject->GetComponent<BC::Text>();

	//Setting new Shape Assignment
	SetNewShapeAssignment();
}

//Override Update method from base Component class
void ShapeAssignmentManager::Update(float deltaTime) {
	Component::Update(deltaTime);
}

//Sets a new shape assignment
ShapeAssignment& ShapeAssignmentManager::SetNewShapeAssignment() {
	//Getting max count as int casted of the ShapeAssignment enum
	int count = (int)ShapeAssignment::Count;
	//Getting random ShapeAssignment value
	ShapeAssignment shapeAssignmentTemp = ShapeAssignment(HelperMethods::GetRandomInt(0, count));

	//Setting current shapeAssignment
	shapeAssignment = shapeAssignmentTemp;

	//Display assignment
	DisplayAssignment();

	//Return the shape assignment
	return shapeAssignment;
}

//Displays the assignment as text
void ShapeAssignmentManager::DisplayAssignment() {
	//String that will hold new content of text
	std::string textContent;

	//Switch on current shapeAssignment
	//Set string content based on value of shapeAssignment
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

	//Setting string content
	shapeAssignmentText->setString(textContent);

	//Get bounds of text content
	sf::FloatRect bounds = shapeAssignmentText->getGlobalBounds();
	//Setting position in center based on bounds
	shapeAssignmentText->setPosition((Window::GetInstance()->GetWindowSize().x / 2) - (bounds.width / 2), Window::GetInstance()->GetWindowSize().y - 50);
}
