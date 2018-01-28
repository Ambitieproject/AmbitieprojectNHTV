#pragma once

#include <iostream>
#include <limits>
#include <math.h>

//Include needed headers files
#include "Component.h"
#include "BaseComponents.hpp"
#include "ShopCategoryItem.h"
#include "ShopItem.h"
#include "FileReadWrite.h"
#include "AudioManager.h"

//Include and use for making use of the Modern JSON library from nlohmann
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
	int LoadCurrency();
	//Save currency method
	int SaveCurrency();

	//Adds a category
	void AddCategory(std::string categoryName, std::string categoryIconFilepath);
	//Sets the position of all categories
	void SetCategoriesPositions();

	//Adds a shop item
	ShopItem& AddShopItem();
	
	//Loads a shop item
	void LoadShopItems(int categoryIndex);
	//Saves a shop item
	void SaveShopItems(int categoryIndex);
	//Buys a shop item
	void BuyShopItem(ShopItem& shopItem);

private:
	//Font used for text
	BC::Font font = BC::Font("../Assets/Fonts/Century Gothic.ttf");

	//Currency text
	BC::Text currencyText = BC::Text(&font);
	//Local currency holder
	int currency;

	//Vector of all the shop categories
	std::vector<ShopCategoryItem*> shopCategoryItems;
	//Vector of all the shop items
	std::vector<ShopItem*> shopItems;

	//Current active category
	int currentActiveCategory;
};

