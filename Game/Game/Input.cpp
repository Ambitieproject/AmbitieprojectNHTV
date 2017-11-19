#include "Input.h"
#include "Window.h"
#include "Game.h"

//Initialise static members

//Window Event, when a Event happens it's basicly input
sf::Event Input::event;

//Pointer to the RenderWindow class
Window* Input::renderWindow;
//Pointer to the window of the RenderWindow class
sf::RenderWindow* Input::window;

//Bool to determine if a key is pressed
bool Input::keyPressed;
//Bool to determine if a mouse button is pressed
bool Input::mouseButtonPressed;

//Local mouse position vector2
sf::Vector2i Input::mousePosition;

//Map that holds the Axis made
std::map<std::string, Axis> Input::InputAxis;

//Copy of the DeltaTime value in the main Game class
float Input::deltaTime;

//Setup Input, sets references
void Input::SetupInput() {
	if (renderWindow == nullptr) {
		//Set RenderWindow references to Game class singleton's RenderWindow class
		renderWindow = Window::GetInstance();
		//Set SFML RenderWindow class
		window = &renderWindow->GetWindow();
	}

	//Set key pressed bool to false
	keyPressed = false;
}

//Update pollEvent method
void Input::UpdatePollEvent(float deltatime) {

	//Set copy of the deltaTime to this class
	deltaTime = deltatime;

	//Make seperate Event just to check basic events
	sf::Event _event;
	
	//PollEvent the sperate Event
	if (window->pollEvent(_event)) {
		//Close window if exit button is pressed
		if (_event.type == sf::Event::Closed) {
			renderWindow->IsClosed = true;
		}
		//Set keypressed bool to false if a key is released
		if (_event.type == sf::Event::KeyReleased) {
			keyPressed = false;
		}
		//Set mouseButtonPressed bool to false if a mouse button is released
		if (_event.type == sf::Event::MouseButtonReleased) {
			mouseButtonPressed = false;
		}
	}

	//Set global Event to the custom Event
	event = _event;
}

//Key pressed method, returns the key pressed state
bool Input::GetKeyPressed(sf::Keyboard::Key key) {
	//Using the standard IsKeyPressed method of SFML
	//and you didn't press a key yet
	if (sf::Keyboard::isKeyPressed(key) && !keyPressed) {
		keyPressed = true;
		return true;
	}
	else {
		return false;
	}
}

//Key down method, returns the key down state
bool Input::GetKeyDown(sf::Keyboard::Key key) {
	//Using the standard IsKeyPressed method of SFML
	if (sf::Keyboard::isKeyPressed(key)) {
		return true;
	}
	return false;
}

//Key released method, returns the key released state
bool Input::GetKeyReleased(sf::Keyboard::Key key) {
	//If the key that is pressed is the given key,
	//and the KeyReleased Event of SFML is called,
	if (event.key.code == key && event.type == sf::Event::KeyReleased) {
		return true;
	}
	else {
		return false;
	}
}

//Any key pressed method, checks for any input from keyboard
bool Input::GetAnyKeyPressed() {
	//Only checks if a keypressed event is called
	if (event.type == sf::Event::KeyPressed) {
		return true;
	}
	else {
		return false;
	}
}

//Any key down method, checks for any input from keyboard
bool Input::GetAnyKeyDown() {
	//Return true if key is already pressed
	if (keyPressed) {
		return true;
	}
	//If key is pressed set keypressed value 
	if (event.type == sf::Event::KeyPressed) {
		keyPressed = true;
	}
	//Return false if keypressed value is false
	if (!keyPressed) {
		return false;
	}
	return false;
}

//Any key released method, checks for any input from keyboard
bool Input::GetAnyKeyReleased() {
	//Only checks if a keyreleased event is called
	if (event.type == sf::Event::KeyReleased) {
		return true;
	}
	else {
		return false;
	}
}

//Mouse button pressed method, returns the mouse button pressed state
bool Input::GetMouseKeyPressed(sf::Mouse::Button mouseButton) {
	//Using the standard IsButtonPressed method of SFML
	//and you didn't press a mouse button yet
	if (sf::Mouse::isButtonPressed(mouseButton) && !mouseButtonPressed) {
		mouseButtonPressed = true;
		return true;
	}
	else {
		return false;
	}
}

//Mouse button down method, returns the mouse button down state
bool Input::GetMouseKeyDown(sf::Mouse::Button mouseButton) {
	//Using the standard IsButtonPressed method of SFML
	if (sf::Mouse::isButtonPressed(mouseButton)) {
		return true;
	}
	else {
		return false;
	}
}

//Mouse button released method, return the mouse button released state
bool Input::GetMouseKeyUp(sf::Mouse::Button mouseButton) {
	//if the key that is pressed is the given key,
	//and the KeyReleased Event of SFML is called,
	if (event.key.code == mouseButton && event.type == sf::Event::MouseButtonReleased) {
		return true;
	}
	else {
		return false;
	}
}

//Method to get the mouse position as a vector2
sf::Vector2i & Input::GetMousePosition() {
	mousePosition = sf::Mouse::getPosition(*window);
	return mousePosition;
}

//Creates an Axis with a positive and negative key that can specified
void Input::CreateAxis(std::string axisName, sf::Keyboard::Key positiveKey, sf::Keyboard::Key negativeKey) {
	Axis axis;
	axis.AxisName = axisName;
	axis.PositiveKey = positiveKey;
	axis.NegativeKey = negativeKey;
	axis.axisMultiplier = 0;

	InputAxis.insert(std::pair<std::string, Axis>(axis.AxisName, axis));
}

//Changes the positive and/or the negative key of an Axis
void Input::ChangeAxis(std::string axisName, ChangeKey changeKey, sf::Keyboard::Key newPositiveKey, sf::Keyboard::Key newNegativeKey) {
	//Make an iterator that goes through all the values in the input axis map and tries to find
	//the axis with the given name
	std::map<std::string, Axis>::iterator it = InputAxis.find(axisName);
	//Create axis pointer
	Axis* axis;
	//If iterator has found an Axis in the map with the given name
	//set the pointer to the iterator value
	//Else return
	if (it != InputAxis.end()) {
		axis = &it->second;
	}
	else {
		std::cout << "No Axis with name " << axisName << " found" << std::endl;
		return;
	}
	
	//Switch that changes the new keys according to the 
	//change key parameter
	switch (changeKey) {
	case ChangeKey::PositiveOnly:
		axis->PositiveKey = newPositiveKey;
		break;
	case ChangeKey::NegativeOnly:
		axis->NegativeKey = newNegativeKey;
		break;
	case ChangeKey::Both:
		axis->PositiveKey = newPositiveKey;
		axis->NegativeKey = newNegativeKey;
		break;
	}
}

//Gets the value of an Axis as a float
float Input::GetAxis(std::string axisName) {
	//Make an iterator that goes through all the values in the input axis map and tries to find
	//the axis with the given name
	std::map<std::string, Axis>::iterator it = InputAxis.find(axisName);
	//Create axis pointer
	Axis* axis;
	//If iterator has found an Axis in the map with the given name
	//set the pointer to the iterator value
	//Else return
	if (it != InputAxis.end()) {
		axis = &it->second;
	}
	else {
		std::cout << "No Axis with name " << axisName << " found" << std::endl;
		return 0.0f;
	}

	//If the positive key of the axis is pressed
	//Increase axis value by amounts
	if (sf::Keyboard::isKeyPressed(axis->PositiveKey)) {
		axis->value = axis->value + (0.25f + axis->axisMultiplier) * deltaTime;
		axis->axisMultiplier = axis->axisMultiplier + 0.01f;
		//Set barrier to be a maximum of 1 for an axis value
		if (axis->value >= 1) {
			axis->value = 1;
			
		}
	}
	//If the negative key of the axis is pressed
	//Decrease axis value by amounts
	if (sf::Keyboard::isKeyPressed(axis->NegativeKey)) {
		axis->value = axis->value - (0.25f - axis->axisMultiplier) * deltaTime;
		axis->axisMultiplier = axis->axisMultiplier - 0.01f;
		//Set barrier to be a minimum of -1 for an axis value
		if (axis->value <= -1) {
			axis->value = -1;
			
		}
	}
	//If positive or negative key of axis has been released
	if (GetKeyReleased(axis->PositiveKey) || GetKeyReleased(axis->NegativeKey)) {
		axis->axisMultiplier = 0;
		axis->value = 0;
	}

	//return Axis value
	return axis->value;
}

//Gets the value of an Axis as a raw int
int Input::GetAxisRaw(std::string axisName) {
	//Make an iterator that goes through all the values in the input axis map and tries to find
	//the axis with the given name
	std::map<std::string, Axis>::iterator it = InputAxis.find(axisName);
	//Create axis pointer
	Axis* axis;
	//If iterator has found an Axis in the map with the given name
	//set the pointer to the iterator value
	//Else return
	if (it != InputAxis.end()) {
		axis = &it->second;
	}
	else {
		std::cout << "No Axis with name " << axisName << " found" << std::endl;
		return 0;
	}

	//If the positive key of the axis is pressed
	//Set the value of the Axis to 1
	if (sf::Keyboard::isKeyPressed(axis->PositiveKey)) {
		axis->value = 1;
	}
	//If the negative key of the axis is pressed
	//Set the value of the Axis to -1
	if (sf::Keyboard::isKeyPressed(axis->NegativeKey)) {
		axis->value = -1;
	}
	//If positive or negative key of axis has been released
	if (GetKeyReleased(axis->PositiveKey) || GetKeyReleased(axis->NegativeKey)) {
		axis->value = 0;
	}

	//return Axis value
	return (int)axis->value;
}
