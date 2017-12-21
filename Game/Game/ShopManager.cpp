#include "ShopManager.h"
#include "GameObject.h"

//Constructor
ShopManager::ShopManager() {

}

//Destructor
ShopManager::~ShopManager() {

}

//Override Start method from base Component class
void ShopManager::Start() {
	Component::Start();

	//Load currency first
	LoadCurrency();

	AddCategory();
	AddCategory();
}

//Override Update method from base Component class
void ShopManager::Update(float deltaTime) {
	Component::Update(deltaTime);

	if (shopCategoryItems.size() > 0) {
		for (int i = 0; i < shopCategoryItems.size(); i++) {
			if (shopCategoryItems[i]->gameObject->GetComponent<BC::BoxCollider>()->OnMouseDown(sf::Mouse::Left)) {
				if (shopCategoryItems[i]->gameObject->GetComponent<BC::Sprite>()->getTexture() != &shopCategoryItems[i]->categoryItemBackgroundPressedTexture) {
					shopCategoryItems[i]->gameObject->GetComponent<BC::Sprite>()->setTexture(shopCategoryItems[i]->categoryItemBackgroundPressedTexture);

					for (int j = 0; j < shopCategoryItems.size(); j++) {
						if (shopCategoryItems[j] != shopCategoryItems[i]) {
							shopCategoryItems[j]->gameObject->GetComponent<BC::Sprite>()->setTexture(shopCategoryItems[j]->categoryItemBackgroundTexture);
						}
					}
				}
			}
		}
	}
}
//Load currency method
float ShopManager::LoadCurrency() {
	json json;
	FileReadWrite::GetJSONFromFile("../Assets/JSON/Currency.json", json);
	return json["Currency"];
}

void ShopManager::AddCategory() {
	//Create GameObject
	GameObject* GOShopCategoryItem = new GameObject("ShopCategoryItem", gameObject->GetScene());
	
	//Create Components
	ShopCategoryItem* shopCategoryItem = new ShopCategoryItem("", "../Assets/Art/Shop/ShopCategoryNotSelected.png", "../Assets/Art/Shop/ShopCategorySelected.png");
	BC::Sprite* categoryItemSprite = new BC::Sprite("../Assets/Art/Shop/ShopCategoryNotSelected.png");
	BC::BoxCollider* categoryItemBoxCollider = new BC::BoxCollider(*categoryItemSprite, sf::Vector2f(0, 0), sf::Vector2f(0, 0));;

	//Set GameObject draw layer
	GOShopCategoryItem->SetDrawIndex(2);

	//Add components
	GOShopCategoryItem->AddComponent(shopCategoryItem);
	GOShopCategoryItem->AddComponent(categoryItemSprite);
	GOShopCategoryItem->AddComponent(categoryItemBoxCollider);

	//Add to vector
	shopCategoryItems.push_back(shopCategoryItem);

	//Set positions of categories
	SetCategoriesPositions();
}

void ShopManager::SetCategoriesPositions() {
	for (int i = 0; i < shopCategoryItems.size(); i++) {

		BC::Sprite* thisSprite = shopCategoryItems[i]->gameObject->GetComponent<BC::Sprite>();
		std::cout << shopCategoryItems.size() << std::endl;
		if (shopCategoryItems.size() > 1) {
			//thisSprite->setPosition(shopCategoryItems[i - 1]->gameObject->GetComponent<BC::Sprite>()->getPosition().x + 100, shopCategoryItems[i - 1]->gameObject->GetComponent<BC::Sprite>()->getPosition().y);
		}
		else {
			thisSprite->setPosition(50, 200);
		}
	}
}
