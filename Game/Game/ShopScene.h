#pragma once
#pragma once

#include <iostream>
#include <string>

//Include Scene header so this class can inherit from Scene
#include "Scene.h"

//Include Base Components so I can make Components in this class
#include "BaseComponents.hpp"

//Include needed headers needed for this scene
#include "ShopManager.h"

//Shop Scene, Custom made Scene class
class ShopScene : public Scene {
public:
	//Constructor
	ShopScene(std::string sceneName);
	//Destructor
	~ShopScene();

	//Override Setup method from base Scene class
	void Setup();
	//Override Start method from base Scene class
	void Start();
	//Override Update method from base Scene class
	void Update(float deltaTime);

private:
	//ShopManager GameObject and components
	GameObject GOShopManager = GameObject("ShopManager", *this);
	ShopManager shopManager = ShopManager();

	//BackgroundBars GameObject and components
	GameObject GOUIBackgroundManager = GameObject("BackgroundManager", *this);
	BC::Sprite backgroundBarTop = BC::Sprite("../Assets/Bar.png");
	BC::Sprite backgroundItemHolder = BC::Sprite("../Assets/Art/Shop/ShopItemHolderBackground.png");
	BC::Sprite backgroundBarBottom = BC::Sprite("../Assets/Bar.png");
	BC::Sprite backgroundCurrencyHolder = BC::Sprite("../Assets/Art/Shop/CurrencyHolderBackground.png");

	//UIManager GameObject and components
	GameObject GOUIManager = GameObject("UIManager", *this);
	BC::Sprite shopTitleText = BC::Sprite("../Assets/Art/Texts/TextShop.png");
	BC::Button buttonBack = BC::Button("../Assets/buttonBack.png");
};
