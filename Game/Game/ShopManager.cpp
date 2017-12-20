#include "ShopManager.h"

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
}

//Override Update method from base Component class
void ShopManager::Update(float deltaTime) {
	Component::Update(deltaTime);
}

//Load currency method
float ShopManager::LoadCurrency() {
	json json;
	FileReadWrite::GetJSONFromFile("../Assets/JSON/Currency.json", json);
	return json["Currency"];
}
