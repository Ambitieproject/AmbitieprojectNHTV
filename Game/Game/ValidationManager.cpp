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
				std::cout << "point from left side" << std::endl;

				checkerSprite->setColor(line[0].color);
			}
		}
		//Faces right from checker
		else {
			collidePointWithChecker = Equations::LineCollide(line[0].position, line[1].position, line[0].position + it->second->GetComponent<ReflectorBeam>()->GetDirection(), p2, p0, *checkerSprite);

			if (collidePointWithChecker != sf::Vector2f(-100, -100)) {
				std::cout << "point from right side" << std::endl;

				checkerSprite->setColor(line[0].color);
			}
		}
	}
}
