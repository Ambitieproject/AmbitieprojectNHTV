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

	//Add first beam
	AddMirror(sf::Vector2f(430, 100), 330);
}

//Override Update method from base Component class
void MirrorManager::Update(float deltaTime) {
	Component::Update(deltaTime);

	//If add mirror button is pressed add a mirror
	if (localAddMirrorButton->IsClicked()) {
		AddMirror(sf::Vector2f(430, 100), 330);
	}

	//If beam map size is bigger then 0
	if (reflectorBeamManager->GetBeams().size() > 0) {
		//For every beam
		for (auto ITBEAMS = reflectorBeamManager->GetBeams().begin(); ITBEAMS != reflectorBeamManager->GetBeams().end(); ITBEAMS++) {
			//If pointer is not equal to a nullptr
			if (ITBEAMS->second != nullptr) {

				//Create variables for checking collision and holding collision data later
				bool CollidesWithAMirror = false;
				std::map<std::string, float> pointsHitDistances;
				GameObject* closestMirror = nullptr;
				float closestDist = 10000000000000000000000000.f;

				//Get beam Component as temp variable
				ReflectorBeam* beam = ITBEAMS->second->GetComponent<ReflectorBeam>();
				sf::Vertex* line = beam->GetLine();

				//If size is bigger then 0
				if (mirrors.size() > 0) {
					//For every mirror
					for (auto ITMIRROR = mirrors.begin(); ITMIRROR != mirrors.end(); ITMIRROR++) {
						//For every beam
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

							//If one of the collision sides is hit
							if (frontsideMirrorCollider != sf::Vector2f(-100, -100) || backsideMirrorCollider != sf::Vector2f(-100, -100) || rightsideMirrorCollider != sf::Vector2f(-100, -100) || leftsideMirrorCollider != sf::Vector2f(-100, -100)) {
								//Calculates direction and distance of that direction
								sf::Vector2f dir = ITMIRROR->second->GetComponent<BC::Sprite>()->getPosition() - line[0].position;
								float dist = sqrt((dir.x * dir.x) + (dir.y * dir.y));

								//If distance is shorter then the already excisting distance
								if (dist < closestDist) {
									//Set variables
									closestDist = dist;
									closestMirror = ITMIRROR->second;
								}
							}
						}
						
					}

					//Radians variable
					float radians = 0;

					//If there is a closest mirror
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

						//If front of mirror is hit
						if (frontsideMirrorCollider != sf::Vector2f(-100, -100)) {
							//Calculate distance between the points
							sf::Vector2f dist = frontsideMirrorCollider - line[0].position;
							//Calculate length of distance vector
							float length = sqrt((dist.x * dist.x) + (dist.y * dist.y));
							//Insert length into map as a pair
							pointsHitDistances.insert(std::pair<std::string, float>("Front", length));
						}
						//If back of mirror is hit
						if (backsideMirrorCollider != sf::Vector2f(-100, -100)) {
							//Calculate distance between the points
							sf::Vector2f dist = backsideMirrorCollider - line[0].position;
							//Calculate length of distance vector
							float length = sqrt((dist.x * dist.x) + (dist.y * dist.y));
							//Insert length into map as a pair
							pointsHitDistances.insert(std::pair<std::string, float>("Back", length));
						}
						//If left of mirror is hit
						if (leftsideMirrorCollider != sf::Vector2f(-100, -100)) {
							//Calculate distance between the points
							sf::Vector2f dist = leftsideMirrorCollider - line[0].position;
							//Calculate length of distance vector
							float length = sqrt((dist.x * dist.x) + (dist.y * dist.y));
							//Insert length into map as a pair
							pointsHitDistances.insert(std::pair<std::string, float>("Left", length));
						}
						//If right of mirror is hit
						if (rightsideMirrorCollider != sf::Vector2f(-100, -100)) {
							//Calculate distance between the points
							sf::Vector2f dist = rightsideMirrorCollider - line[0].position;
							//Calculate length of distance vector
							float length = sqrt((dist.x * dist.x) + (dist.y * dist.y));
							//Insert length into map as a pair
							pointsHitDistances.insert(std::pair<std::string, float>("Right", length));
						}

						//If hit distances map size is bigger then 0
						if (pointsHitDistances.size() > 0) {
							//Set variables
							CollidesWithAMirror = true;
							beam->reflectingMirror = closestMirror;

							//Get first element in hit distances map
							std::map<std::string, float>::iterator shortestDist = pointsHitDistances.begin();

							//For every element in map
							for (auto it = pointsHitDistances.begin(); it != pointsHitDistances.end(); it++) {
								//Check if distance of iterator is shorter then first element
								if (it->second < shortestDist->second) {
									//If so set variables
									shortestDist = it;
								}
							}

							//Shortest distance is Front
							if (shortestDist->first == "Front") {
								//Set position of end of laser
								line[1].position = frontsideMirrorCollider;

								//Create needed points
								sf::Vector2f pointA;
								sf::Vector2f pointB;
								sf::Vector2f pointC;
								sf::Vector2f pointD;

								//Create needed differences
								sf::Vector2f diffAC;
								sf::Vector2f diffCB;
								sf::Vector2f diffAD;
								sf::Vector2f diffAB;

								//Create needed distance lengths
								float lengthAC;
								float lengthCB;
								float lengthAD;
								float lengthAB;

								//To determine if radians should be added to or removed from rotation on beam
								bool plusRadians = true;

								//Create standard length to calculate with
								float distLength = 20;

								//Set pointA depending on which side is colliding
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

								//Calculate pointB
								pointB = pointA - beam->GetDirection() * distLength;
								//Calculate pointC
								pointC = pointA + Equations::CreateDirectionFromRotation(closestMirror->GetComponent<BC::Sprite>()->getRotation()) * distLength;

								//Calculate differenc vectors
								diffAC = pointC - pointA;
								diffCB = pointC - pointB;
								diffAB = pointB - pointA;

								//Calculate pointD
								pointD = pointC - (diffCB * 0.5f);

								//Calculate differenc vector
								diffAD = pointD - pointA;

								//Calculate lengths
								lengthAC = sqrt((diffAC.x * diffAC.x) + (diffAC.y * diffAC.y));
								lengthCB = sqrt((diffCB.x * diffCB.x) + (diffCB.y * diffCB.y));
								lengthAD = sqrt((diffAD.x * diffAD.x) + (diffAD.y * diffAD.y));
								lengthAB = sqrt((diffAB.x * diffAB.x) + (diffAB.y * diffAB.y));

								//Calculate radians with the help of cosinus
								radians = acos(lengthAD / lengthAB) * 180 / PI;
								//Multiply radians by 2
								radians = radians * 2;

#pragma region CanDO?
								gameObject->SetDrawIndex(0);

								if (Input::GetKeyPressed(sf::Keyboard::T)) {
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
								}
#pragma endregion
								//If mirror is not static
								if (!closestMirror->GetComponent<Mirror>()->IsStaticObject()) {
									//If new beam of beam is not yet made
									if (!beam->newBeam) {
										//Create beam
										GameObject* go = &reflectorBeamManager->AddBeam(frontsideMirrorCollider, closestMirror->GetComponent<BC::Sprite>()->getRotation() + radians, line[0].color);

										//Set variables for new beam
										beam->newBeam = go;
										beam->newBeam->GetComponent<ReflectorBeam>()->NoRotationBeam = true;
										beam->newBeam->GetComponent<ReflectorBeam>()->mirrorSpawningFrom = closestMirror;
									}
									//If beam is already created
									else {
										//Set begin line of beam
										beam->newBeam->GetComponent<ReflectorBeam>()->GetLine()[0].position = frontsideMirrorCollider;

										//Calculate new direction of beam
										sf::Vector2f dir = Equations::CreateDirectionFromRotation(closestMirror->GetComponent<BC::Sprite>()->getRotation() + radians);
										//Set direction of beam
										beam->newBeam->GetComponent<ReflectorBeam>()->SetDirection(dir);

										//Get x and y value of already excisting beam round by 2 decimal points
										float beamX = roundf(beam->GetDirection().x * 100) / 100;
										float beamY = roundf(beam->GetDirection().y * 100) / 100;

										//Get x and y value of new beam round by 2 decimal points
										float newBeamX = roundf(beam->newBeam->GetComponent<ReflectorBeam>()->GetDirection().x * 100) / 100;
										float newBeamY = roundf(beam->newBeam->GetComponent<ReflectorBeam>()->GetDirection().y * 100) / 100;

										//Flip positive or negative to other way around
										newBeamX = newBeamX * -1;
										newBeamY = newBeamY * -1;

										//If values are equal to each other
										if (newBeamX == beamX && newBeamY == beamY) {
											//Create new direction with rotation minus
											sf::Vector2f dir = Equations::CreateDirectionFromRotation(closestMirror->GetComponent<BC::Sprite>()->getRotation() - radians);
											//Set direction
											beam->newBeam->GetComponent<ReflectorBeam>()->SetDirection(dir);
										}
									}
								}
							}
							//Shortest distance is Back
							else if (shortestDist->first == "Back") {
								//Set end of line position
								line[1].position = backsideMirrorCollider;

								//If new beam excist desroy it
								if (beam->newBeam) {
									beam->DestroyNewLaser();
								}
							}
							//Shortest distance is Left
							else if (shortestDist->first == "Left") {
								//Set end of line position
								line[1].position = leftsideMirrorCollider;
								
								//If new beam excist desroy it
								if (beam->newBeam) {
									beam->DestroyNewLaser();
								}
							}
							//Shortest distance is Right
							else if (shortestDist->first == "Right") {
								//Set end of line position
								line[1].position = rightsideMirrorCollider;

								//If new beam excist desroy it
								if (beam->newBeam) {
									beam->DestroyNewLaser();
								}
							}
						}
					}

					//Clear hit distances map
					pointsHitDistances.clear();

					//If beam is not colliding with a mirror
					if (!CollidesWithAMirror) {
						//Set variable
						beam->reflectingMirror = nullptr;
					}

					//If reflecting mirror of beam is nullptr
					if (!beam->reflectingMirror || mirrors.size() == 0) {
						//Set line end to shoot straight ahead
						line[1].position = line[0].position + sf::Vector2f(beam->GetDirection().x * 1000, beam->GetDirection().y * 1000);

						//If new beam excist desroy it
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
