#include "ReflectorBeam.h"
#include "GameObject.h"
#include "SceneManager.h"



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
	}
}

void ReflectorBeam::Update(float deltaTime) {
	Component::Update(deltaTime);

	SetBeamColor();

	for (auto it = beams.begin(); it != beams.end(); it++) {
		Collider* stayOverlapCollider = it->second->beamBoxCollider.OnStayOverlap();

		if (stayOverlapCollider && stayOverlapCollider->GameObject->Name == "MirrorManager") {
			if (mirrorManager->IsMovingAMirror()) {
				ResetBeam();
			}
		}
		else {
			if (it->second->beam.getScale().y != 1000) {
				it->second->beam.setScale(it->second->beam.getScale().x, it->second->beam.getScale().y - 10 * deltaTime);
			}
		}
	}

	
}

void ReflectorBeam::AddBeam(Beam* beam) {
	GameObject->AddComponent(&beam->beam);
	GameObject->AddComponent(&beam->beamBoxCollider);
	
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

void ReflectorBeam::ResetBeam() {
	for (auto it = beams.begin(); it != beams.end(); it++) {
		
	}

	//beams.clear();
}
