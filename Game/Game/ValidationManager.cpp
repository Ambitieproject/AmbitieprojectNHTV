#include "ValidationManager.h"

//Constructor
ValidationManager::ValidationManager(BC::Sprite* checkerSprite, ReflectorBeamManager* reflectorBeamManager) : checkerSprite(checkerSprite), reflectorBeamManager(reflectorBeamManager) {

}

//Destructor
ValidationManager::~ValidationManager() {

}

//Override Start method from base Component class
void ValidationManager::Start() {
	Component::Start();

	validation = false;
}

//Override Update method from base Component class
void ValidationManager::Update(float deltaTime) {
	Component::Update(deltaTime);

	sf::Vector2f p0 = checkerSprite->gameObject->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(checkerSprite->gameObject->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(0));
	sf::Vector2f p1 = checkerSprite->gameObject->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(checkerSprite->gameObject->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(1));
	sf::Vector2f p2 = checkerSprite->gameObject->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(checkerSprite->gameObject->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(2));
	sf::Vector2f p3 = checkerSprite->gameObject->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(checkerSprite->gameObject->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(3));

	for (auto it = reflectorBeamManager->GetBeams().begin(); it != reflectorBeamManager->GetBeams().end(); it++) {
		sf::Vector2f collidePointWithChecker;

		sf::Vertex* line = it->second->GetComponent<ReflectorBeam>()->GetLine();

		//Faces left from checker
		if (line[0].position.x < checkerSprite->getPosition().x) {
			collidePointWithChecker = Equations::LineCollide(line[0].position, line[1].position, line[0].position + it->second->GetComponent<ReflectorBeam>()->GetDirection(), p3, p1, *checkerSprite);

			if (collidePointWithChecker != sf::Vector2f(-100, -100)) {

				//Make iterator and try to find this object in already existing map
				if (std::find(activeValidationColors.begin(), activeValidationColors.end(), line[0].color) == activeValidationColors.end()) {
					activeValidationColors.push_back(line[0].color);
					CheckLaserCountColor();
				}
			}
			else {
				for (auto it = activeValidationColors.begin(); it != activeValidationColors.end(); ) {
					if (it._Ptr == &line[0].color) {
						it = activeValidationColors.erase(it);
					}
					else {
						++it;
					}
				}
			}
		}
		//Faces right from checker
		else {
			collidePointWithChecker = Equations::LineCollide(line[0].position, line[1].position, line[0].position + it->second->GetComponent<ReflectorBeam>()->GetDirection(), p2, p0, *checkerSprite);

			if (collidePointWithChecker != sf::Vector2f(-100, -100)) {

				//Make iterator and try to find this object in already existing map
				if (std::find(activeValidationColors.begin(), activeValidationColors.end(), line[0].color) == activeValidationColors.end()) {
					activeValidationColors.push_back(line[0].color);
					CheckLaserCountColor();
				}
			}
			else {
				for (auto it = activeValidationColors.begin(); it != activeValidationColors.end(); ) {
					if (it._Ptr == &line[0].color) {
						it = activeValidationColors.erase(it);
					}
					else {
						++it;
					}
				}
			}
		}
	}
}

bool ValidationManager::Validate() {
	return validation;
}

bool ValidationManager::CheckLaserCountColor() {
	int count = 0;
	for (auto it = activeValidationColors.begin(); it < activeValidationColors.end(); it++) {
		if (*it._Ptr == sf::Color::Red) {
			count++;
		}
		else if (*it._Ptr == sf::Color(255, 153, 0)) {
			count++;
		}
		else if (*it._Ptr == sf::Color::Yellow) {
			count++;
		}
		else if (*it._Ptr == sf::Color::Green) {
			count++;
		}
		else if (*it._Ptr == sf::Color::Blue) {
			count++;
		}
		else if (*it._Ptr == sf::Color(153, 0, 204)) {
			count++;
		}
	}

	if (count >= 6) {
		std::cout << "done" << std::endl;
		validation = true;
	}
	return false;
}
