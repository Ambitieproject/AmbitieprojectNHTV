#pragma once

#include <iostream>

//Include needed headers files
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

	//Set the category name
	std::string SetCategoryName(std::string name);
	//Get the category name
	std::string GetCategoryName();

	//Not pressed Item background texture
	sf::Texture categoryItemBackgroundTexture;
	//Pressed Item background texture
	sf::Texture categoryItemBackgroundPressedTexture;

private:
	//Category name
	std::string categoryName;
};

