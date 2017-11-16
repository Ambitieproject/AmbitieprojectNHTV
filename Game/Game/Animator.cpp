#include "Animator.h"
#include "GameObject.h"

using namespace BC;

//Constructor
Animator::Animator() {

}

//Destructor
Animator::~Animator() {
}

//Override Start method from base Component class
void Animator::Start() {
	Component::Start();

	//For length of components
	//If component is AnimationClip then add to list
	for (auto it = GameObject->Components.begin(); it != GameObject->Components.end(); it++) {
		BC::AnimationClip* animationClip = dynamic_cast<BC::AnimationClip*>(it->second);

		if (animationClip) {
			Animations.push_back(animationClip);
		}
	}
}

//Override Update method from base Component class
void Animator::Update(float deltaTime) {
	Component::Update(deltaTime);
}

//Play animation with a parameter value
AnimationClip* Animator::PlayAnimation(std::string animationName) {
	
	if (currentAnimationClip != nullptr) {
		currentAnimationClip->Stop();
	}
	
	//For length of components
	//Play animation, set pointer and return
	for (auto it = Animations.begin(); it != Animations.end(); it++) {
		if (it._Ptr->_Myval->GetName() == animationName) {
			currentAnimationClip = it._Ptr->_Myval;
			currentAnimationClip->Play();
			return currentAnimationClip;
		}
	}

	//If not found cout a message and return nothing
	std::cout << "Could not find animation with name " << currentAnimationClip->GetName() << std::endl;
	return nullptr;
}

//Stop animation
AnimationClip* Animator::StopAnimation() {
	currentAnimationClip->Stop();
	return currentAnimationClip;
}
