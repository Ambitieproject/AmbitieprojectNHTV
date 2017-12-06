#include "TimeManager.h"
#include "GameObject.h"



TimeManager::TimeManager()
{
}


TimeManager::~TimeManager()
{
}

void TimeManager::Start() {
	Component::Start();

	timeText = gameObject->GetComponent<BC::Text>();

	minutes = 0;
	clock = sf::seconds(130);
}

void TimeManager::Update(float deltaTime) {
	Component::Update(deltaTime);

	while (clock.asSeconds() - 60 > 0) {
		clock -= sf::seconds(60);
		minutes++;
	}

	clock -= sf::seconds(deltaTime);
	int time = clock.asSeconds();
	std::cout << minutes << std::endl;

	if (minutes >= 10) {
		if (clock.asSeconds() >= 10) {
			timeText->setString(std::to_string(minutes) + ":" + std::to_string(time));
		}
		else {
			timeText->setString(std::to_string(minutes) + ":" + "0" + std::to_string(time));
		}
	}
	else {
		if (clock.asSeconds() >= 10) {
			timeText->setString("0" + std::to_string(minutes) + ":" + std::to_string(time));
		}
		else {
			timeText->setString("0" + (std::to_string(minutes) + ":" + "0" + std::to_string(time)));
		}
	}
	
}
