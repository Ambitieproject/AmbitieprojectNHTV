#include "ReflectorBeam.h"
#include "GameObject.h"
#include "MirrorManager.h"
#include "ReflectorBeamManager.h"

ReflectorBeam::ReflectorBeam(MirrorManager* mirrorManager, ReflectorBeamManager* reflectorBeamManager) : mirrorManager(mirrorManager), reflectorBeamManager(reflectorBeamManager) {
	growSpeed = 10.0f;
	isReflecting = false;
	reflectorBeamSprite.rotate(180);
	beamReflectMirror = nullptr;
}

ReflectorBeam::~ReflectorBeam()
{
}

void ReflectorBeam::Update(float deltaTime) {
	//Get begin, stay and end overlap colliders
	Collider* beginOverlapCollider = reflectorBeamBoxCollider.OnBeginOverlap();
	Collider* stayOverlapCollider = reflectorBeamBoxCollider.OnStayOverlap();
	Collider* endOverlapCollider = reflectorBeamBoxCollider.OnEndOverlap();
	//If begin collider is not nullptr and the gameobject colliding is a mirror
	if (beginOverlapCollider && beginOverlapCollider->gameObject->Name == "Mirror") {
		if (beginOverlapCollider->gameObject != cantReflectMirror) {
			//set Reflecting to true;
			isReflecting = true;
		}
		
	}
	//If end collider is not nullptr and the gameobject colliding is a mirror
	if (endOverlapCollider && endOverlapCollider->gameObject->Name == "Mirror") {
		if (endOverlapCollider->gameObject != cantReflectMirror) {
			//set Reflecting to true;
			isReflecting = false;
		}
	}

	if (isReflecting && mirrorManager->IsMovingAMirror()) {
		sf::Sprite* sprite = stayOverlapCollider->gameObject->GetComponent<BC::Sprite>();
		float diff = std::abs(mirrorManager->GetPositionsInMirror(sprite, positions));
		if (diff > 0) {
			reflectorBeamSprite.setScale(reflectorBeamSprite.getScale().x, reflectorBeamSprite.getScale().y - ((growSpeed * deltaTime) * diff));
		}

		if (!beamReflectMirror) {
			beamReflectMirror = stayOverlapCollider->gameObject;
			//ReflectorBeam& newBeam = reflectorBeamManager->AddBeam(positions.back(), 180 + beamReflectMirror->GetComponent<BC::Sprite>()->getRotation());
			//newBeam.cantReflectMirror = beamReflectMirror;
		}
	}
	else if(!isReflecting) {
		if (reflectorBeamSprite.getScale().y != 1000) {
			Grow(deltaTime);

			if (beamReflectMirror) {
				beamReflectMirror = nullptr;
			}
		}
	}
}

void ReflectorBeam::Grow(float deltaTime) {
	reflectorBeamSprite.setScale(reflectorBeamSprite.getScale().x, reflectorBeamSprite.getScale().y + (growSpeed * deltaTime));

	sf::Vector2f newPos = sf::Vector2f(
		reflectorBeamSprite.getPosition().x - (reflectorBeamSprite.getTexture()->getSize().x * reflectorBeamSprite.getScale().x), 
		reflectorBeamSprite.getPosition().y - (reflectorBeamSprite.getTexture()->getSize().y * reflectorBeamSprite.getScale().y)
	);
	
	positions.push_back(newPos);
}

void ReflectorBeam::SetGrowSpeed(float growSpeed) {
	this->growSpeed = growSpeed;
}

BC::Sprite& ReflectorBeam::GetSprite() {
	return reflectorBeamSprite;
}

BC::BoxCollider& ReflectorBeam::GetBoxCollider() {
	return reflectorBeamBoxCollider;
}

std::vector<sf::Vector2f>& ReflectorBeam::GetPositions() {
	return positions;
}

float ReflectorBeam::GetGrowSpeed() {
	return growSpeed;
}

GameObject * ReflectorBeam::GetBeamReflectMirror()
{
	return nullptr;
}

bool ReflectorBeam::IsReflecting() {
	return isReflecting;
}

void ReflectorBeam::SetReflecting(bool state) {
	isReflecting = state;
}
