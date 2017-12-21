#pragma once

#include <iostream>
#include <limits>
#include <math.h>

#include "Component.h"
#include "BaseComponents.hpp"
#include "ShopCategoryItem.h"

#include "FileReadWrite.h"

//Include and use for making use of the Modern JSON library frmo nlohmann
//For more information go to the json hpp file 
#include "json.hpp"
using json = nlohmann::json;

//ShopManager Component
class ShopManager : public Component {
public:
	//Constructor
	ShopManager();
	//Destructor
	~ShopManager();

	//Override Start method from base Component class
	void Start();
	//Override Update method from base Component class
	void Update(float deltaTime);

private:
	//Load currency method
	float LoadCurrency();

	void AddCategory();
	void SetCategoriesPositions();

private:
	std::vector<ShopCategoryItem*> shopCategoryItems;
};

