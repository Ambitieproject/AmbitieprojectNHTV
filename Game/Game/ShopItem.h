#pragma once

#include <iostream>
#include <string>

//Include needed headers files
#include "Component.h"
#include "BaseComponents.hpp"

//ShopItem struct
struct ShopItem : public Component {
public:
	//Item category
	std::string Category;
	//Item intensity
	int ItemIntensity;
	//Item bought value
	bool Bought;
	//Item cost
	int Cost;
	//Item description
	std::string Description;
};

