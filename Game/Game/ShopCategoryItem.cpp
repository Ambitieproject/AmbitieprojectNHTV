#include "ShopCategoryItem.h"
#include "GameObject.h"

//Constructor
ShopCategoryItem::ShopCategoryItem(std::string categoryItemSpritePath, std::string categoryItemBackgroundPath, std::string categoryItemBackgroundPressedPath) {
	//Load textures
	categoryItemBackgroundTexture.loadFromFile(categoryItemBackgroundPath);
	categoryItemBackgroundPressedTexture.loadFromFile(categoryItemBackgroundPressedPath);
}

//Destructor
ShopCategoryItem::~ShopCategoryItem() {

}

//Override Start method from base Component class
void ShopCategoryItem::Start() {
	Component::Start();
}

//Override Update method from base Component class
void ShopCategoryItem::Update(float deltaTime) {
	Component::Update(deltaTime);
}

//Set the category name
std::string ShopCategoryItem::SetCategoryName(std::string name) {
	//Set name
	categoryName = name;
	//Return name
	return categoryName;
}

//Get the category name
std::string ShopCategoryItem::GetCategoryName() {
	return categoryName;
}
