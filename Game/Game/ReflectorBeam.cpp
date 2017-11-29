#include "ReflectorBeam.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Window.h"



ReflectorBeam::ReflectorBeam(std::string beamFilePath) : beamFilePath(beamFilePath) {
	beamIndex = 0;
}


ReflectorBeam::~ReflectorBeam()
{
}

void ReflectorBeam::Start() {

	//Setting references
	prisma = SceneManager::GetActiveScene().FindGameObjectByName("Prisma")->GetComponent<BC::Sprite>();
	prismaMovementController = SceneManager::GetActiveScene().FindGameObjectByName("Prisma")->GetComponent<PrismaMovementController>();
	mirrorManager = SceneManager::GetActiveScene().FindGameObjectByName("MirrorManager")->GetComponent<MirrorManager>();

	sf::Image colorValueImage;
	colorValueImage.loadFromFile("../Assets/colorScheme.png");

	for (int i = 0; i < colorValueImage.getSize().x; i++) {
		prismaColors.push_back(colorValueImage.getPixel(i, 0));
	}

	currentPrismaColorIndex = 0;
	currentPrismaColor = prismaColors[currentPrismaColorIndex];

	Beam* beam = new Beam();
	AddBeam(beam);

	beam->beam.setPosition(prisma->getPosition());
	beam->beam.setPosition(beam->beam.getPosition().x, beam->beam.getPosition().y - 70);

	for (auto it = beams.begin(); it != beams.end(); it++) {
		it->second->beam.setColor(currentPrismaColor);
		it->second->beam.rotate(180);
		it->second->positions.push_back(it->second->beam.getPosition());
	}
}

void ReflectorBeam::Update(float deltaTime) {
	Component::Update(deltaTime);

	SetBeamColor();

	//for every beam
	for (auto it = beams.begin(); it != beams.end(); it++) {

		if (mirrorManager->IsMovingAMirror()) {
			if (mirrorManager->GetCurrentMirror()) {
				BC::BoxCollider* boxCol = mirrorManager->GetCurrentMirror()->GetComponent<BC::BoxCollider>();

				if (it->second->beamBoxCollider.BoundingBoxTest(it->second->beamBoxCollider.GetBoxCollider(), boxCol->GetBoxCollider())) {
					std::cout << "Collision" << std::endl;
				}
			}
			
		}
		

		/*
		//Get begin, stay and end overlap colliders
		Collider* beginOverlapCollider = it->second->beamBoxCollider.OnBeginOverlap();
		Collider* stayOverlapCollider = it->second->beamBoxCollider.OnStayOverlap();
		Collider* endOverlapCollider = it->second->beamBoxCollider.OnEndOverlap();

		//If begin collider is not nullptr and the gameobject colliding is a mirror
		if (beginOverlapCollider && beginOverlapCollider->gameObject->Name == "Mirror") {
			//set Reflecting to true;
			it->second->isReflecting = true;
		}
		if (stayOverlapCollider && stayOverlapCollider->gameObject->Name == "Mirror") {
			//set Reflecting to true;
			std::cout << "COLLIDE" << std::endl;
		}
		//If end collider is not nullptr and the gameobject colliding is a mirror
		if (endOverlapCollider && endOverlapCollider->gameObject->Name == "Mirror") {
			//set Reflecting to false;
			it->second->isReflecting = false;
		}
		
		if (it->second->isReflecting) {
			sf::Sprite sprite = stayOverlapCollider->GetSpriteCast();
			std::vector<sf::Vector2f> positionsBeam = it->second->positions;
			float diff = std::abs(mirrorManager->GetPositionsInMirror(&sprite, positionsBeam));
			if (diff > 0) {
				it->second->beam.setScale(it->second->beam.getScale().x, it->second->beam.getScale().y - (diff * deltaTime));
			}
		}
		else {
			if (it->second->beam.getScale().y != 1000) {
				it->second->beam.setScale(it->second->beam.getScale().x, it->second->beam.getScale().y + 10 * deltaTime);
				sf::Vector2f newPos = sf::Vector2f(it->second->beam.getPosition().x - (it->second->beam.getTexture()->getSize().x * it->second->beam.getScale().x), it->second->beam.getPosition().y - (it->second->beam.getTexture()->getSize().y * it->second->beam.getScale().y));
				it->second->positions.push_back(newPos);
			}
		}
		*/
	}

	
}

void ReflectorBeam::AddBeam(Beam* beam) {
	gameObject->AddComponent(&beam->beam);
	gameObject->AddComponent(&beam->beamBoxCollider);
	beams.insert(std::pair<int, Beam*>(beamIndex, beam));
	beamIndex++;
}

void ReflectorBeam::SetBeamColor() {
	if (prismaMovementController->IsMovingRight()) {
		if (currentPrismaColorIndex >= prismaColors.size() - 1) {
			currentPrismaColorIndex = 0;
		}

		currentPrismaColorIndex++;
		currentPrismaColor = prismaColors[currentPrismaColorIndex];

		for (auto it = beams.begin(); it != beams.end(); it++) {
			it->second->beam.setColor(currentPrismaColor);
		}
	}
	if (prismaMovementController->IsMovingLeft()) {
		if (currentPrismaColorIndex < 0 + 1) {
			currentPrismaColorIndex = prismaColors.size();
		}

		currentPrismaColorIndex--;
		currentPrismaColor = prismaColors[currentPrismaColorIndex];

		for (auto it = beams.begin(); it != beams.end(); it++) {
			it->second->beam.setColor(currentPrismaColor);
		}
	}
}
