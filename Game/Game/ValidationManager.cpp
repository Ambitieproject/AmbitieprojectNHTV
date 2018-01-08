#include "ValidationManager.h"
#include "GameObject.h"

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
	validatedSprakleImage = nullptr;
}

//Override Update method from base Component class
void ValidationManager::Update(float deltaTime) {
	Component::Update(deltaTime);
	
	//If sparkle image is not equal to a nullptr
	if (validatedSprakleImage != nullptr) {
		//Rotate iamge
		validatedSprakleImage->rotate(200 * deltaTime);
		//Increase scale of image
		validatedSprakleImage->setScale(validatedSprakleImage->getScale().x + 200 * deltaTime, validatedSprakleImage->getScale().y + 200 * deltaTime);

		return;
	}

	//For every point of the checker sprite get the point
	sf::Vector2f p0 = checkerSprite->gameObject->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(checkerSprite->gameObject->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(0));
	sf::Vector2f p1 = checkerSprite->gameObject->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(checkerSprite->gameObject->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(1));
	sf::Vector2f p2 = checkerSprite->gameObject->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(checkerSprite->gameObject->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(2));
	sf::Vector2f p3 = checkerSprite->gameObject->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(checkerSprite->gameObject->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(3));

	//For every beam
	for (auto it = reflectorBeamManager->GetBeams().begin(); it != reflectorBeamManager->GetBeams().end(); it++) {
		//If beam is not equal to nullptr
		if (it->second != nullptr) {
			//Create sf::Vector2f
			sf::Vector2f collidePointWithChecker;

			//Get line of laser
			sf::Vertex* line = it->second->GetComponent<ReflectorBeam>()->GetLine();
			
			//Faces left from checker
			if (line[0].position.x < checkerSprite->getPosition().x) {
				//Check with line collision
				collidePointWithChecker = Equations::LineCollide(line[0].position, line[1].position, it->second->GetComponent<ReflectorBeam>()->GetDirection(), p3, p1, *checkerSprite);

				//If line collision is hit
				if (collidePointWithChecker != sf::Vector2f(-100, -100)) {
					//Make iterator and try to find this object in already existing map
					//If so pushback the laser color and check the laser count
					if (std::find(activeValidationColors.begin(), activeValidationColors.end(), line[0].color) == activeValidationColors.end()) {
						activeValidationColors.push_back(line[0].color);
						CheckLaserCountColor();
					}
				}
				//If laser is not hit
				else {
					//For every laser in the activeValidationColors vector
					for (auto it = activeValidationColors.begin(); it != activeValidationColors.end(); ) {
						//If iterator is equal to the color of the current line
						if (it._Ptr->r == line[0].color.r && it._Ptr->g == line[0].color.g && it._Ptr->b == line[0].color.b && it._Ptr->a == line[0].color.a) {
							//Erase line from vector
							it = activeValidationColors.erase(it);
						}
						//Else increase iterator
						else {
							++it;
						}
					}
				}
			}
			//Faces right from checker
			else {
				//Check with line collision
				collidePointWithChecker = Equations::LineCollide(line[0].position, line[1].position, it->second->GetComponent<ReflectorBeam>()->GetDirection(), p2, p0, *checkerSprite);
				
				//If line collision is hit
				if (collidePointWithChecker != sf::Vector2f(-100, -100)) {
					//Make iterator and try to find this object in already existing map
					//If so pushback the laser color and check the laser count
					if (std::find(activeValidationColors.begin(), activeValidationColors.end(), line[0].color) == activeValidationColors.end()) {
						activeValidationColors.push_back(line[0].color);
						CheckLaserCountColor();
					}
				}
				//If laser is not hit
				else {
					//For every laser in the activeValidationColors vector
					for (auto it = activeValidationColors.begin(); it != activeValidationColors.end(); ) {
						//If iterator is equal to the color of the current line
						if (it._Ptr->r == line[0].color.r && it._Ptr->g == line[0].color.g && it._Ptr->b == line[0].color.b && it._Ptr->a == line[0].color.a) {	
							//Erase line from vector
							it = activeValidationColors.erase(it);
						}
						//Else increase iterator
						else {
							++it;
						}
					}
				}
			}
		}
	}
}

//Checks for validation
bool ValidationManager::Validate() {
	return validation;
}

//Checks the laser count
bool ValidationManager::CheckLaserCountColor() {
	//Create count
	int count = 0;

	//For the length of the activeValidationColors vector
	for (auto it = activeValidationColors.begin(); it < activeValidationColors.end(); it++) {
		//Check if laser has certain color
		//If so then increase count

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

	//If count is equal to the exact same number as there are different lasers
	if (count >= 6) {
		//Create sparkle image
		validatedSprakleImage = new BC::Sprite("../Assets/Art/Images/FlashImage.png");

		//Set default values for sparkle image
		validatedSprakleImage->setOrigin(validatedSprakleImage->getTexture()->getSize().x * 0.5f, validatedSprakleImage->getTexture()->getSize().y * 0.5f);
		validatedSprakleImage->setPosition(checkerSprite->getPosition());
		
		//Add sparkle image as a Component to the GameObject
		gameObject->AddComponent(validatedSprakleImage);

		//Set validation to be true
		validation = true;
	}

	//If code reaches this part then return false
	return false;
}
