#include "ColorManager.h"

//Constructor
ColorManager::ColorManager() {

}

//Destructor
ColorManager::~ColorManager() {

}

//Override Start method from base Component class
void ColorManager::Awake() {
	Component::Awake();

	//Make and load an image of a color scheme
	sf::Image colorValueImage;
	colorValueImage.loadFromFile("../Assets/colorScheme.png");
	std::cout << "pushing colors" << std::endl;
	//Push back every pixel of the color scheme to the vector on the x as
	for (int i = 0; i < colorValueImage.getSize().x; i++) {
		colors.push_back(colorValueImage.getPixel(i, 0));
	}
}

//Override Update method from base Component class
void ColorManager::Update(float deltaTime) {
	Component::Update(deltaTime);
}

//Gets the colors
std::vector<sf::Color>& ColorManager::GetColors() {
	return colors;
}
