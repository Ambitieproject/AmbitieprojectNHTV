#include "ScoreManager.h"
#include "GameObject.h"

//Constructor
ScoreManager::ScoreManager(MirrorManager& mirrorManager, TimeManager& timeManager) : mirrorManager(mirrorManager), timeManager(timeManager) {

}

//Destructor
ScoreManager::~ScoreManager() {

}

//Override Start method from base Component class
void ScoreManager::Start() {
	Component::Start();

	//Setting variables to start value
	score = 0;
	maxScore = 10000;
}

//Override Update method from base Component class
void ScoreManager::Update(float deltaTime) {
	Component::Update(deltaTime);
}

//Adjusts score by a specific parameter
int ScoreManager::AdjustScore(int adjustment) {
	//Set and return score
	score = score + adjustment;
	return score;
}

//Get extra mirrors from shop
int ScoreManager::GetExtraMirrorsFromShop() {
	//Create JSON object
	json json;
	//Get data from file into JSON object
	FileReadWrite::GetJSONFromFile("../Assets/JSON/ShopItems.json", json);

	//Create index
	int index = 0;

	//For JSON object size
	for (int i = 0; i < json.size(); i++) {
		//for JSON object size within the already flowing for loop
		for (int j = 0; j < json[i].size(); j++) {
			//If category of JSON object value is equal to "Mirror"
			if (json[i]["Shop Items"][j]["Category"] == "Mirror") {
				//Set index
				index = i;
			}
		}
	}

	//Create index
	int mirrorCount = 0;

	//If size of Shop Items list is bigger then 0
	if (json[index]["Shop Items"].size() > 0) {
		//for JSON object size within the already flowing for loop
		for (int i = 0; i < json[index]["Shop Items"].size(); i++) {

			//Get values from JSON object value
			bool bought = json[index].at("Shop Items")[i]["Bought"].get<bool>();
			std::string category = json[index].at("Shop Items")[i]["Category"].get<std::string>();
			int itemIntensity = json[index].at("Shop Items")[i]["Item intensity"].get<int>();

			//If the item is bought and the JSON object value is equal to "Mirror"
			if (bought && category == "Mirror") {
				//If this items itemIntesity is bigger then the already
				//existing itemIntensity
				if (itemIntensity > mirrorCount) {
					//Set itemIntensity
					mirrorCount = itemIntensity;
				}
			}
		}
	}

	//Return mirrorCount
	return mirrorCount;
}

//Get extra time from shop
int ScoreManager::GetExtraTimeFromShop() {
	//Create JSON object
	json json;
	//Get data from file into JSON object
	FileReadWrite::GetJSONFromFile("../Assets/JSON/ShopItems.json", json);

	//Create index
	int index = 0;

	//For JSON object size
	for (int i = 0; i < json.size(); i++) {
		//for JSON object size within the already flowing for loop
		for (int j = 0; j < json[i].size(); j++) {
			//If category of JSON object value is equal to "Time"
			if (json[i]["Shop Items"][j]["Category"] == "Time") {
				//Set index
				index = i;
			}
		}
	}

	//Create index
	int secondsCount = 0;

	//If size of Shop Items list is bigger then 0
	if (json[index]["Shop Items"].size() > 0) {
		//for JSON object size within the already flowing for loop
		for (int i = 0; i < json[index]["Shop Items"].size(); i++) {

			//Get values from JSON object value
			bool bought = json[index].at("Shop Items")[i]["Bought"].get<bool>();
			std::string category = json[index].at("Shop Items")[i]["Category"].get<std::string>();
			int itemIntensity = json[index].at("Shop Items")[i]["Item intensity"].get<int>();

			//If the item is bought and the JSON object value is equal to "Time"
			if (bought && category == "Time") {
				//If this items itemIntesity is bigger then the already
				//existing itemIntensity
				if (itemIntensity > secondsCount) {
					//Set itemIntensity
					secondsCount = itemIntensity;
				}
			}
		}
	}

	//Return secondsCount
	return secondsCount;
}

//Gets the score
int ScoreManager::GetScore() {
	return score;
}

//Gets the final score
int ScoreManager::GetFinalScore() {
	//Adjust score with maxScore
	AdjustScore(maxScore);

	//Calculate mirrorCount
	int mirrorCount = mirrorManager.GetMirrors().size() - (3 + GetExtraMirrorsFromShop());
	
	//If count is bigger then 0
	if (mirrorCount > 0) {
		//For the length of the count
		//Adjust the score every time
		for (int i = 0; i < mirrorCount; i++) {
			AdjustScore(-100);
		}
	}

	//Calculate timeToDecrease
	int timeToDecrase = timeManager.GetTimeInSeconds() - (10 + GetExtraTimeFromShop());

	//If the variable is bigger then 0
	if (timeToDecrase > 0) {
		//Adjust score
		AdjustScore(-timeToDecrase);
	}
	
	//If total score is bigger then 0
	//return score
	if (score > 0) {
		return score;
	}
	//else return 0
	else {
		return 0;
	}
}
