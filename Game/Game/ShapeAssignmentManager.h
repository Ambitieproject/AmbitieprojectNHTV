#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <map>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"

#include "BaseComponents.hpp"

#include "ColorManager.h"

//Enum that holds the different shape assignment options available
enum ShapeAssignment {
	Triangle,
	Square,
	Trapezoid,
	Parrallelogram,
	Rectangle,
	Count
};

//ShapeAssignmentManager class
class ShapeAssignmentManager : public Component {
public:
	//Constructor
	ShapeAssignmentManager();
	//Destructor
	~ShapeAssignmentManager();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

	//Sets a new shape assignment
	ShapeAssignment& SetNewShapeAssignment();

private:
	//Displays the assignment as text
	void DisplayAssignment();

private:
	//Local shape assignment enum holder
	ShapeAssignment shapeAssignment;

	//Local color assignment
	sf::Color* assignmentColor;

	//Shape assignment display text
	BC::Text* shapeAssignmentText;

	//Color Manager reference
	ColorManager* colorManager;
};

