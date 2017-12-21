#include "ShopCategoryItem.h"
#include "GameObject.h"

//Constructor
ShopCategoryItem::ShopCategoryItem(std::string categoryItemSpritePath, std::string categoryItemBackgroundPath, std::string categoryItemBackgroundPressedPath) {
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
