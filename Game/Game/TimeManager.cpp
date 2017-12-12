#include "TimeManager.h"
#include "GameObject.h"


//Constructor
TimeManager::TimeManager() {
	
}

//Destructor
TimeManager::~TimeManager() {

}

//Override Start method from base Component class
void TimeManager::Start() {
	Component::Start();

	//Setting variables to begin value
	minutes = 0;
	seconds = 0;
	totalTime = 0;

	canCount = true;

	//Getting Text component of GameObject
	timeText = gameObject->GetComponent<BC::Text>();
}

//Override Update method from base Component class
void TimeManager::Update(float deltaTime) {
	Component::Update(deltaTime);

	if (canCount) {
		//Increase totalTime
		totalTime += deltaTime;

		if (totalTime >= 1) {
			//Setting totalTime to 1 just to be sure it is rounded
			totalTime = 1;

			//If seconds is 59 add 1 minute to the minute variable and reset seconds
			if (seconds == 59) {
				seconds = -1;
				minutes++;
			}

			//Increase seconds by the totalTime as an int
			seconds = seconds + (int)totalTime;

			//Resetting totalTime
			totalTime = 0;
		}

		//If minutes is bigger then 10
		if (minutes >= 10) {
			//Seconds bigger then 10
			if (seconds >= 10) {
				//Set text
				timeText->setString(std::to_string(minutes) + ":" + std::to_string(seconds));
			}
			//Seconds not bigger then 10
			else {
				//Set text
				timeText->setString(std::to_string(minutes) + ":" + "0" + std::to_string(seconds));
			}
		}
		//Minutes is not bigger then 10
		else {
			//Seconds bigger then 10
			if (seconds >= 10) {
				//Set text
				timeText->setString("0" + std::to_string(minutes) + ":" + std::to_string(seconds));
			}
			//Seconds not bigger then 10
			else {
				//Set text
				timeText->setString("0" + (std::to_string(minutes) + ":" + "0" + std::to_string(seconds)));
			}
		}
	}
}
