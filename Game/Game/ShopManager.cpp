#include "ShopManager.h"
#include "GameObject.h"
#include "SceneManager.h"

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

	//Add categories
	AddCategory("SelfReflections");
	AddCategory("GameItems");

	//Load all the items of the first category
	LoadShopItems(0);

	//Set first category of cateogry vector to be active
	shopCategoryItems[0]->gameObject->GetComponent<BC::Sprite>()->setTexture(shopCategoryItems[0]->categoryItemBackgroundPressedTexture);
	currentActiveCategory = 0;
}

//Override Update method from base Component class
void ShopManager::Update(float deltaTime) {
	Component::Update(deltaTime);

	//Update currency text
	currencyText.setString(std::to_string(currency));

	//As long as the size of the vector is bigger then 0
	if (shopCategoryItems.size() > 0) {
		//For every category
		for (int i = 0; i < shopCategoryItems.size(); i++) {
			//If category is clicked reset texture, reset and load shop items of that category and set the current active category
			if (shopCategoryItems[i]->gameObject->GetComponent<BC::BoxCollider>()->OnMouseDown(sf::Mouse::Left)) {
				if (shopCategoryItems[i]->gameObject->GetComponent<BC::Sprite>()->getTexture() != &shopCategoryItems[i]->categoryItemBackgroundPressedTexture) {
					shopCategoryItems[i]->gameObject->GetComponent<BC::Sprite>()->setTexture(shopCategoryItems[i]->categoryItemBackgroundPressedTexture);
					LoadShopItems(i);
					currentActiveCategory = i;

					//For every category,
					//set new texture for category
					for (int j = 0; j < shopCategoryItems.size(); j++) {
						if (shopCategoryItems[j] != shopCategoryItems[i]) {
							shopCategoryItems[j]->gameObject->GetComponent<BC::Sprite>()->setTexture(shopCategoryItems[j]->categoryItemBackgroundTexture);
						}
					}
				}
			}
		}
	}

	//As long as the size of the vector is bigger then 0
	if (shopItems.size() > 0) {
		//For every shop item
		for (int i = 0; i < shopItems.size(); i++) {
			//If shop item is not yet bought
			if (!shopItems[i]->Bought) {
				//If shop item buy button is clicked then buy the item, save the item and update and save the currency etc...
				if (shopItems[i]->gameObject->GetComponent<BC::Button>()->IsClicked()) {
					//Buy item
					BuyShopItem(*shopItems[i]);
					//Save shop items
					SaveShopItems(currentActiveCategory);
					//Save currency
					SaveCurrency();
					//Reload shopItems
					LoadShopItems(currentActiveCategory);
				}
			}
		}
	}
}

//Load currency method
int ShopManager::LoadCurrency() {
	//Create JSON object
	json json;
	//Get data from file into JSON object
	FileReadWrite::GetJSONFromFile("../Assets/JSON/Currency.json", json);
	//Set currency from JSON object
	currency = json["Currency"];

	//Set basic values of the currency text
	currencyText.setColor(sf::Color::Black);
	currencyText.setPosition(305, 87);
	currencyText.setString(std::to_string(currency));

	//Add component to GameObject
	gameObject->AddComponent(&currencyText);
	
	//Return currency
	return currency;
}

int ShopManager::SaveCurrency() {
	//Create JSON object
	json json;
	//Push currency into JSON object
	json["Currency"] = currency;
	//Save data to file
	FileReadWrite::WriteJSONToFile("../Assets/JSON/Currency.json", json);
	//Return currency
	return currency;
}

//Adds a category
void ShopManager::AddCategory(std::string categoryName) {
	//Create GameObject
	GameObject* GOShopCategoryItem = new GameObject("ShopCategoryItem", gameObject->GetScene());
	
	//Create Components
	ShopCategoryItem* shopCategoryItem = new ShopCategoryItem("", "../Assets/Art/Shop/ShopCategoryNotSelected.png", "../Assets/Art/Shop/ShopCategorySelected.png");
	BC::Sprite* categoryItemSprite = new BC::Sprite("../Assets/Art/Shop/ShopCategoryNotSelected.png");
	BC::BoxCollider* categoryItemBoxCollider = new BC::BoxCollider(*categoryItemSprite, sf::Vector2f(0, 0), sf::Vector2f(0, 0));;

	//Set GameObject draw layer
	GOShopCategoryItem->SetDrawIndex(2);

	//Add Components
	GOShopCategoryItem->AddComponent(shopCategoryItem);
	GOShopCategoryItem->AddComponent(categoryItemSprite);
	GOShopCategoryItem->AddComponent(categoryItemBoxCollider);

	//Add to vector
	shopCategoryItems.push_back(shopCategoryItem);

	//Set default values for sprite
	categoryItemSprite->setScale(0.6f, 0.6f);

	//Set default values for shopCategoryItem
	shopCategoryItem->SetCategoryName(categoryName);

	//Set positions of categories
	SetCategoriesPositions();
}

//Sets the position of all categories
void ShopManager::SetCategoriesPositions() {
	//For every category
	for (int i = 0; i < shopCategoryItems.size(); i++) {
		//Get component of category
		BC::Sprite* thisSprite = shopCategoryItems[i]->gameObject->GetComponent<BC::Sprite>();

		//If i value is bigger then 0
		if (i > 0) {
			//Set position relative to previous category item
			if (shopCategoryItems.size() > 1) {
				thisSprite->setPosition(shopCategoryItems[i - 1]->gameObject->GetComponent<BC::Sprite>()->getPosition().x + 100, shopCategoryItems[i - 1]->gameObject->GetComponent<BC::Sprite>()->getPosition().y);
			}
		}
		else {
			//Set position
			thisSprite->setPosition(20, 100);
		}
	}
}

//Adds a shop item
ShopItem& ShopManager::AddShopItem() {
	//Create new GameObject
	GameObject* go = new GameObject("ShopItem", gameObject->GetScene());

	//Create Components
	BC::Sprite* goSprite = new BC::Sprite("../Assets/Art/Shop/ShopItemBackground.png");
	ShopItem* goShopItem = new ShopItem();

	//Set drawing index layer
	go->SetDrawIndex(2);

	//Set default values for sprite
	goSprite->setScale(0.4f, 0.4f);

	//Add new shop item to vector
	shopItems.push_back(goShopItem);

	//Adds Components to GameObject
	go->AddComponent(goSprite);
	go->AddComponent(goShopItem);

	//Return the new shop item
	return *goShopItem;
}

//Loads a shop item
void ShopManager::LoadShopItems(int categoryIndex) {
	//Get list of all Shop Items
	std::vector<GameObject*> goList = gameObject->GetScene().FindGameObjectsByName("ShopItem");

	//Delete all shop items
	if (goList.size() > 0) {
		for (int i = 0; i < goList.size(); i++) {
			gameObject->GetScene().DestroyGameObject(goList[i]);
		}
	}

	//Clear vector
	shopItems.clear();

	//Create JSON object
	json json;
	//Get data from file into JSON object
	FileReadWrite::GetJSONFromFile("../Assets/JSON/ShopItems.json", json);

	//If size of Shop Items list is bigger then 0
	if (json[categoryIndex]["Shop Items"].size() > 0) {
		//Create default x and y position values
		float x = 40;
		float y = 200;

		int it = 2;

		//For every shop item
		for (int i = 0; i < json[categoryIndex]["Shop Items"].size(); i++) {
			//Make Shop Item
			ShopItem& shopItem = AddShopItem();

			//Push values from JSON Object to shopItem
			shopItem.Category = json[categoryIndex].at("Shop Items")[i]["Category"].get<std::string>();
			shopItem.ItemIntensity = json[categoryIndex].at("Shop Items")[i]["Item intensity"].get<int>();
			shopItem.Bought = json[categoryIndex].at("Shop Items")[i]["Bought"].get<bool>();
			shopItem.Cost = json[categoryIndex].at("Shop Items")[i]["Cost"].get<int>();
			shopItem.Description = json[categoryIndex].at("Shop Items")[i]["Description"].get<std::string>();

			//If i value is bigger then 0
			if (i > 0) {
				//Set positions
				shopItem.gameObject->GetComponent<BC::Sprite>()->setPosition(x + 235, y);
				x = shopItem.gameObject->GetComponent<BC::Sprite>()->getPosition().x;

				//If iterator int value is 2 meaning 2 objects are next to each other,
				//reset x and y values
				if (it == 2) {
					it = 0;
					x = -195;
					y = y + 150;
				}

				//Increase iterator int value
				it++;
			}
			else {
				//Set positions
				shopItem.gameObject->GetComponent<BC::Sprite>()->setPosition(x, y);
				x = shopItem.gameObject->GetComponent<BC::Sprite>()->getPosition().x;
				y = shopItem.gameObject->GetComponent<BC::Sprite>()->getPosition().y;
			}

			//If shop item is not yet bought
			if (!shopItem.Bought) {
				//Get texture out of gameObjects sprite and reset it
				sf::Texture& texture = shopItem.gameObject->GetComponent<BC::Sprite>()->GetTexture();
				texture.loadFromFile("../Assets/Art/Shop/ShopItemUsedBackground.png");
				shopItem.gameObject->GetComponent<BC::Sprite>()->setTexture(texture);
			
				//Create buy button for shop item
				BC::Button* shopItemButton = new BC::Button("../Assets/Art/Buttons/ShopBuy/ButtonBuyNormal.png", "../Assets/Art/Buttons/ShopBuy/ButtonBuyHovered.png", "../Assets/Art/Buttons/ShopBuy/ButtonBuyPressed.png");

				//Set default values of shop item buy button
				shopItemButton->GetCurrentButtonSprite().setScale(0.5f, 0.5f);
				shopItemButton->GetCurrentButtonSprite().setPosition(shopItem.gameObject->GetComponent<BC::Sprite>()->getPosition().x + 35, shopItem.gameObject->GetComponent<BC::Sprite>()->getPosition().y + 80);

				//Create shopCostText
				BC::Text* shopCostText = new BC::Text(&font);

				//Set text standard values
				shopCostText->setScale(0.5f, 0.5f);
				shopCostText->setString(std::to_string(shopItem.Cost));
				shopCostText->setColor(sf::Color::Black);

				//center text
				sf::FloatRect textRect = shopCostText->getLocalBounds();
				shopCostText->setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				shopCostText->setPosition(shopItem.gameObject->GetComponent<BC::Sprite>()->getPosition().x + 83, shopItem.gameObject->GetComponent<BC::Sprite>()->getPosition().y + 70);

				//Add Components to GameObject
				shopItem.gameObject->AddComponent(shopItemButton);
				shopItem.gameObject->AddComponent(shopCostText);
			}

			//Create ifo text for shop item
			BC::Text* shopInfoText = new BC::Text(&font);

			//Set text standard values
			shopInfoText->setScale(0.4f, 0.4f);
			shopInfoText->setString(shopItem.Description);
			shopInfoText->setColor(sf::Color::White);

			if (!shopItem.Bought && shopItem.Category == "Selfreflection Info") {
				shopInfoText->setString("?");
			}

			//center text
			sf::FloatRect textRect = shopInfoText->getLocalBounds();
			shopInfoText->setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			shopInfoText->setPosition(shopItem.gameObject->GetComponent<BC::Sprite>()->getPosition().x + 83, shopItem.gameObject->GetComponent<BC::Sprite>()->getPosition().y + 30);
			shopItem.gameObject->AddComponent(shopInfoText);
		}
	}
}

//Saves a shop item
void ShopManager::SaveShopItems(int categoryIndex) {
	//Create JSON object
	json json;
	//Get data from file into JSON object
	FileReadWrite::GetJSONFromFile("../Assets/JSON/ShopItems.json", json);
	//For every shopItem
	for (int i = 0; i < shopItems.size(); i++) {
		//Push values into JSON object
		json[categoryIndex]["Shop Items"][i]["Category"] = shopItems[i]->Category;
		json[categoryIndex]["Shop Items"][i]["Item intensity"] = shopItems[i]->ItemIntensity;
		json[categoryIndex]["Shop Items"][i]["Bought"] = shopItems[i]->Bought;
		json[categoryIndex]["Shop Items"][i]["Cost"] = shopItems[i]->Cost;
		json[categoryIndex]["Shop Items"][i]["Description"] = shopItems[i]->Description;
	}
	//Write new data from JSON object to file
	FileReadWrite::WriteJSONToFile("../Assets/JSON/ShopItems.json", json);
}

//Buys a shop item
void ShopManager::BuyShopItem(ShopItem& shopItem) {	
	//If currency is bigger or equal to the cost you need for this shopItem
	if (currency >= shopItem.Cost) {
		//Set bought value of shopItem to true
		shopItem.Bought = true;

		//Create temp value for the cost of shopItem and the currency
		int cost = (int)shopItem.Cost;
		int currencyInt = (int)currency;

		//Decrease temp value
		currencyInt = currencyInt - cost;

		//Set currency to temp currency
		currency = currencyInt;

		//Set color of currencyText just for indicating
		currencyText.setColor(sf::Color::Black);
	}
	else {
		//Set color of currencyText just for indicating
		currencyText.setColor(sf::Color::Red);
	}
}
