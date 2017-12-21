#pragma once

#include <iostream>
#include <limits>
#include <math.h>

#include "Component.h"
#include "BaseComponents.hpp"

//Category shop component
class ShopCategoryItem : public Component {
public:
	//Constructor
	ShopCategoryItem(std::string categoryItemSpritePath, std::string categoryItemBackgroundPath, std::string categoryItemBackgroundPressedPath);
	//Destructor
	~ShopCategoryItem();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

	sf::Texture categoryItemBackgroundTexture;
	sf::Texture categoryItemBackgroundPressedTexture;

private:
	
};

