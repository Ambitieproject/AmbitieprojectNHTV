#include "MirrorManager.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Window.h"

//Constructor
MirrorManager::MirrorManager(BC::Button* addMirrorButton, ReflectorBeamManager* reflectorBeamManager) : localAddMirrorButton(addMirrorButton), reflectorBeamManager(reflectorBeamManager) {
	
}

//Destructor
MirrorManager::~MirrorManager() {

}

//Override Start method from base Component class
void MirrorManager::Start() {
	Component::Start();
}

//Override Update method from base Component class
void MirrorManager::Update(float deltaTime) {
	Component::Update(deltaTime);

	//If add mirror button is pressed add a mirror
	if (localAddMirrorButton->IsClicked()) {
		AddMirror(sf::Vector2f(430, 100), 330);
	}

	if (reflectorBeamManager->GetBeams().size() > 0) {
		//For every beam
		for (auto ITBEAMS = reflectorBeamManager->GetBeams().begin(); ITBEAMS != reflectorBeamManager->GetBeams().end(); ITBEAMS++) {
			if (ITBEAMS->second != nullptr) {
				bool CollidesWithAMirror = false;
				std::map<std::string, float> pointsHitDistances;

				//Get beam Component as temp variable
				ReflectorBeam* beam = ITBEAMS->second->GetComponent<ReflectorBeam>();
				sf::Vertex* line = beam->GetLine();

				GameObject* closestMirror = nullptr;
				float closestDist = 10000000000000000000000000.f;
				if (mirrors.size() > 0) {
					//For every mirror
					for (auto ITMIRROR = mirrors.begin(); ITMIRROR != mirrors.end(); ITMIRROR++) {
						if (beam->mirrorSpawningFrom != ITMIRROR->second) {
							//Get the four points of the mirror object
							//Top left, top right, bottom right, bottom left
							sf::Vector2f p0 = ITMIRROR->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(ITMIRROR->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(0));
							sf::Vector2f p1 = ITMIRROR->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(ITMIRROR->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(1));
							sf::Vector2f p2 = ITMIRROR->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(ITMIRROR->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(2));
							sf::Vector2f p3 = ITMIRROR->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(ITMIRROR->second->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(3));

							//Create the line detection vectors
							sf::Vector2f frontsideMirrorCollider;
							sf::Vector2f backsideMirrorCollider;
							sf::Vector2f rightsideMirrorCollider;
							sf::Vector2f leftsideMirrorCollider;

							//Line detections with the front, back, right side and left side of the mirror and the laser
							frontsideMirrorCollider = Equations::LineCollide(line[0].position, line[1].position, beam->GetDirection(), p0, p1, *ITMIRROR->second->GetComponent<BC::Sprite>());
							backsideMirrorCollider = Equations::LineCollide(line[0].position, line[1].position, beam->GetDirection(), p3, p2, *ITMIRROR->second->GetComponent<BC::Sprite>());
							rightsideMirrorCollider = Equations::LineCollide(line[0].position, line[1].position, beam->GetDirection(), p1, p2, *ITMIRROR->second->GetComponent<BC::Sprite>());
							leftsideMirrorCollider = Equations::LineCollide(line[0].position, line[1].position, beam->GetDirection(), p0, p3, *ITMIRROR->second->GetComponent<BC::Sprite>());

							if (frontsideMirrorCollider != sf::Vector2f(-100, -100) || backsideMirrorCollider != sf::Vector2f(-100, -100) || rightsideMirrorCollider != sf::Vector2f(-100, -100) || leftsideMirrorCollider != sf::Vector2f(-100, -100)) {
								sf::Vector2f dir = ITMIRROR->second->GetComponent<BC::Sprite>()->getPosition() - line[0].position;
								float dist = sqrt((dir.x * dir.x) + (dir.y * dir.y));

								if (dist < closestDist) {
									closestDist = dist;
									closestMirror = ITMIRROR->second;
								}
							}
						}
						
					}
					float radians = 0;
					if (closestMirror) {
						//Get the four points of the mirror object
						//Top left, top right, bottom right, bottom left
						sf::Vector2f p0 = closestMirror->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(closestMirror->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(0));
						sf::Vector2f p1 = closestMirror->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(closestMirror->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(1));
						sf::Vector2f p2 = closestMirror->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(closestMirror->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(2));
						sf::Vector2f p3 = closestMirror->GetComponent<BC::BoxCollider>()->GetBoxCollider().getTransform().transformPoint(closestMirror->GetComponent<BC::BoxCollider>()->GetBoxCollider().getPoint(3));

						//Create the line detection vectors
						sf::Vector2f frontsideMirrorCollider;
						sf::Vector2f backsideMirrorCollider;
						sf::Vector2f rightsideMirrorCollider;
						sf::Vector2f leftsideMirrorCollider;

						//Line detections with the front, back, right side and left side of the mirror and the laser
						frontsideMirrorCollider = Equations::LineCollide(line[0].position, line[1].position, beam->GetDirection(), p0, p1, *closestMirror->GetComponent<BC::Sprite>());
						backsideMirrorCollider = Equations::LineCollide(line[0].position, line[1].position, beam->GetDirection(), p3, p2, *closestMirror->GetComponent<BC::Sprite>());
						rightsideMirrorCollider = Equations::LineCollide(line[0].position, line[1].position, beam->GetDirection(), p1, p2, *closestMirror->GetComponent<BC::Sprite>());
						leftsideMirrorCollider = Equations::LineCollide(line[0].position, line[1].position, beam->GetDirection(), p0, p3, *closestMirror->GetComponent<BC::Sprite>());

						if (frontsideMirrorCollider != sf::Vector2f(-100, -100)) {
							sf::Vector2f dist = frontsideMirrorCollider - line[0].position;
							float length = sqrt((dist.x * dist.x) + (dist.y * dist.y));
							pointsHitDistances.insert(std::pair<std::string, float>("Front", length));
						}
						if (backsideMirrorCollider != sf::Vector2f(-100, -100)) {
							sf::Vector2f dist = backsideMirrorCollider - line[0].position;
							float length = sqrt((dist.x * dist.x) + (dist.y * dist.y));
							pointsHitDistances.insert(std::pair<std::string, float>("Back", length));
						}
						if (leftsideMirrorCollider != sf::Vector2f(-100, -100)) {
							sf::Vector2f dist = leftsideMirrorCollider - line[0].position;
							float length = sqrt((dist.x * dist.x) + (dist.y * dist.y));
							pointsHitDistances.insert(std::pair<std::string, float>("Left", length));
						}
						if (rightsideMirrorCollider != sf::Vector2f(-100, -100)) {
							sf::Vector2f dist = rightsideMirrorCollider - line[0].position;
							float length = sqrt((dist.x * dist.x) + (dist.y * dist.y));
							pointsHitDistances.insert(std::pair<std::string, float>("Right", length));
						}

						if (pointsHitDistances.size() > 0) {
							CollidesWithAMirror = true;
							beam->reflectingMirror = closestMirror;

							std::map<std::string, float>::iterator shortestDist = pointsHitDistances.begin();

							for (auto it = pointsHitDistances.begin(); it != pointsHitDistances.end(); it++) {
								if (it->second < shortestDist->second) {
									shortestDist = it;
								}
							}
							
							if (shortestDist->first == "Front") {
								line[1].position = frontsideMirrorCollider;

								sf::Vector2f pointA;
								sf::Vector2f pointB;
								sf::Vector2f pointC;
								sf::Vector2f pointD;

								sf::Vector2f diffAC;
								sf::Vector2f diffCB;
								sf::Vector2f diffAD;

								float lengthAC;
								float lengthCB;
								float lengthAD;



								float distLength = 20;

								if (shortestDist->first == "Front") {
									pointA = frontsideMirrorCollider;
								}
								else if (shortestDist->first == "Back") {
									pointA = backsideMirrorCollider;
								}
								else if (shortestDist->first == "Left") {
									pointA = leftsideMirrorCollider;
								}
								else if (shortestDist->first == "Right") {
									pointA = rightsideMirrorCollider;
								}

								pointB = pointA - beam->GetDirection() * distLength;
								pointC = pointA + Equations::CreateDirectionFromRotation(closestMirror->GetComponent<BC::Sprite>()->getRotation()) * distLength;

								diffAC = pointC - pointA;
								diffCB = pointC - pointB;

								pointD = pointC - (diffCB * 0.5f);

								diffAD = pointD - pointA;

								lengthAC = sqrt((diffAC.x * diffAC.x) + (diffAC.y * diffAC.y));
								lengthCB = sqrt((diffCB.x * diffCB.x) + (diffCB.y * diffCB.y));
								lengthAD = sqrt((diffAD.x * diffAD.x) + (diffAD.y * diffAD.y));

								radians = atan((lengthCB / 2) / lengthAD) * 180 / PI;
								radians = radians * 2;

								std::cout << closestMirror->GetComponent<BC::Sprite>()->getRotation() + radians << std::endl;
								std::cout << radians << std::endl;
								/*
								gameObject->SetDrawIndex(0);

								BC::Sprite* spritePointA = new BC::Sprite("../Assets/Art/Images/FlashImage.png");
								spritePointA->setOrigin(spritePointA->getTexture()->getSize().x * 0.5f, spritePointA->getTexture()->getSize().y * 0.5f);
								spritePointA->setPosition(pointA);
								spritePointA->setColor(sf::Color::Red);
								gameObject->AddComponent(spritePointA);

								BC::Sprite* spritePointB = new BC::Sprite("../Assets/Art/Images/FlashImage.png");
								spritePointB->setOrigin(spritePointB->getTexture()->getSize().x * 0.5f, spritePointB->getTexture()->getSize().y * 0.5f);
								spritePointB->setPosition(pointB);
								spritePointB->setColor(sf::Color::Blue);
								gameObject->AddComponent(spritePointB);

								BC::Sprite* spritePointC = new BC::Sprite("../Assets/Art/Images/FlashImage.png");
								spritePointC->setOrigin(spritePointC->getTexture()->getSize().x * 0.5f, spritePointC->getTexture()->getSize().y * 0.5f);
								spritePointC->setPosition(pointC);
								spritePointC->setColor(sf::Color::Green);
								gameObject->AddComponent(spritePointC);

								BC::Sprite* spritePointD = new BC::Sprite("../Assets/Art/Images/FlashImage.png");
								spritePointD->setOrigin(spritePointD->getTexture()->getSize().x * 0.5f, spritePointD->getTexture()->getSize().y * 0.5f);
								spritePointD->setPosition(pointD);
								spritePointD->setColor(sf::Color::Yellow);
								gameObject->AddComponent(spritePointD);
								*/

								if (!beam->newBeam) {
									GameObject* go = &reflectorBeamManager->AddBeam(frontsideMirrorCollider, closestMirror->GetComponent<BC::Sprite>()->getRotation() + radians, line[0].color);

									beam->newBeam = go;
									beam->newBeam->GetComponent<ReflectorBeam>()->mirrorSpawningFrom = closestMirror;
								}
								else {
									beam->newBeam->GetComponent<ReflectorBeam>()->GetLine()[0].position = frontsideMirrorCollider;
								}	
							}
							else if (shortestDist->first == "Back") {
								line[1].position = backsideMirrorCollider;

								if (beam->newBeam) {
									beam->DestroyNewLaser();
								}
							}
							else if (shortestDist->first == "Left") {
								line[1].position = leftsideMirrorCollider;

								if (beam->newBeam) {
									beam->DestroyNewLaser();
								}
							}
							else if (shortestDist->first == "Right") {
								line[1].position = rightsideMirrorCollider;

								if (beam->newBeam) {
									beam->DestroyNewLaser();
								}
							}
						}
					}

					pointsHitDistances.clear();

					if (!CollidesWithAMirror) {
						beam->reflectingMirror = nullptr;
					}

					if (!beam->reflectingMirror) {

						if (beam->mirrorSpawningFrom)
							beam->beamRotation = beam->mirrorSpawningFrom->GetComponent<BC::Sprite>()->getRotation() + radians;

						line[1].position = line[0].position + sf::Vector2f(beam->GetDirection().x * 1000, beam->GetDirection().y * 1000);

						if (beam->newBeam) {
							beam->DestroyNewLaser();
						}
					}
				}
			}
		}
	}
	//If mirror size is bigger then 0
	if (mirrors.size() > 0) {
		//For every mirror call the Move method when mirror is being moved
		//Then return out of this method so that only one mirror can be moved
		for (auto it = mirrors.begin(); it != mirrors.end(); it++) {
			if (!it->second->GetComponent<Mirror>()->IsStaticObject()) {
				if (it->second->GetComponent<Mirror>()->IsMoving()) {
					it->second->GetComponent<Mirror>()->Move(deltaTime);
					return;
				}
				else {
					it->second->GetComponent<Mirror>()->Move(deltaTime);
				}
			}
		}		
	}
}

//Adds a mirror
Mirror& MirrorManager::AddMirror(sf::Vector2f position, float rotation) {
	//Make mirror GameObject
	GameObject* mirror = new GameObject("Mirror", gameObject->GetScene());

	//Set mirror draw index
	mirror->SetDrawIndex(3);

	//Make components
	Mirror* mirrorComponent = new Mirror();
	BC::Sprite* mirrorSprite = new BC::Sprite("../Assets/Mirror2.png");
	BC::BoxCollider* mirrorBoxCollider = new BC::BoxCollider(*mirrorSprite, sf::Vector2f(0, 0), sf::Vector2f(0, 0));

	//Add components to GameObject
	mirror->AddComponent(mirrorComponent);
	mirror->AddComponent(mirrorSprite);
	mirror->AddComponent(mirrorBoxCollider);

	//Set a rotation of the mirror
	mirrorSprite->rotate(rotation);

	//Setting mirrorComponent standard values
	mirrorComponent->SetIsStaticObject(false);

	//Set origin of mirror sprite to be in the middle
	mirrorSprite->setOrigin(mirrorSprite->GetTexture().getSize().x / 2, mirrorSprite->GetTexture().getSize().y / 2);
	//Set position to be random across the window width size
	mirrorSprite->setPosition(position);

	//Add mirror to the mirror list and increment the index of that list
	mirrors.insert(std::pair<int, GameObject*>(mirrorIndex, mirror));
	mirrorIndex++;

	//Return mirror component
	return *mirrorComponent;
}

//Returns if a mirror is being moved
bool MirrorManager::IsMovingAMirror() {
	//Go through all the mirrors, if one is moving return true
	for (auto it = mirrors.begin(); it != mirrors.end(); it++) {
		if (it->second->GetComponent<Mirror>()->IsMoving()) {
			return true;
		}
	}
	//If no mirror is moving return false
	return false;
}

//Gets the mirror map
std::map<int, GameObject*>& MirrorManager::GetMirrors() {
	return mirrors;
}

//Gets the current active mirror
GameObject* MirrorManager::GetCurrentMirror() {
	return currentMirror;
}
