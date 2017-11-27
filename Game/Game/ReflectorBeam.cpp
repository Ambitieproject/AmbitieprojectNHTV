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

	prisma = SceneManager::GetActiveScene().FindGameObjectByName("Prisma")->GetComponent<BC::Sprite>();
	mirrorManager = SceneManager::GetActiveScene().FindGameObjectByName("MirrorManager")->GetComponent<MirrorManager>();

	Beam* beam = new Beam();
	AddBeam(beam);

	beam->beam.setPosition(prisma->getPosition());
	beam->beam.setPosition(beam->beam.getPosition().x, beam->beam.getPosition().y - 70);
}

void ReflectorBeam::Update(float deltaTime) {
	Component::Update(deltaTime);

	for (auto it = beams.begin(); it != beams.end(); it++) {
		Collider* stayOverlapCollider = it->second->beamBoxCollider.OnStayOverlap();

		if (stayOverlapCollider && stayOverlapCollider->GameObject->Name == "MirrorManager") {
			if (mirrorManager->IsMovingAMirror()) {
				ResetBeam();
			}
		}
		else {
			if (it->second->beam.getScale().y != 1000) {
				std::cout << it->second->beam.getScale().y << std::endl;
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

void ReflectorBeam::ResetBeam() {
	for (auto it = beams.begin(); it != beams.end(); it++) {
		
	}

	//beams.clear();
}
