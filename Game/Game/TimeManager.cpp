#include "TimeManager.h"
#include "GameObject.h"


//Constructor
TimeManager::TimeManager(int timeInSeconds) {
	//Setting variables to begin value
	seconds = timeInSeconds;

	minutes = 0;
	totalTime = 0;

	canCount = true;
}

//Destructor
TimeManager::~TimeManager() {

}

//Override Start method from base Component class
void TimeManager::Start() {
	Component::Start();

	//Getting Text component of GameObject
	timeText = gameObject->GetComponent<BC::Text>();

	//Devide seconds by 60 as an int, this way it will return the minutes
	minutes = seconds / 60;
	//For each minute there is remove 60 seconds from the seconds variable
	for (int i = 0; i < minutes; i++) {
		seconds = seconds - 60;
	}
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

			//If seconds is 0 and minutes not then reset counter to 60 seconds
			//and remove 1 minute from the minute variable
			if (seconds == 0 && minutes != 0) {
				seconds = 60;
				minutes--;
			}

			//If seconds and minutes are 0 then counter has ended and you return
			if (seconds == 0) {
				if (minutes == 0) {
					canCount = false;
					return;
				}
			}

			//Decrease seconds by the totalTime as an int
			seconds = seconds - (int)totalTime;

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
