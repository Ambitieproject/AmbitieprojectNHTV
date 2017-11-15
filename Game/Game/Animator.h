#pragma once

#include <iostream>
#include <map>
#include <list>
#include <string>

#include <SFML\Graphics.hpp>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"

//Include supper class component
#include "AnimationClip.h"

//Namespace Base Component
namespace BC {
	//Animator class which handles the handling of animation switching, pausing, playing and stopping
	class Animator : public Component {
	public:
		//Constructor
		Animator();
		//Destructor
		~Animator();

		//Override Start method from base Component class
		void Start();
		//Override Update method from base Component class
		void Update(float deltaTime);

		//Play animation with a parameter value
		AnimationClip* PlayAnimation(std::string animationName);
		//Stop animation
		AnimationClip* StopAnimation();

	private:
		//All animations list
		std::list<AnimationClip> Animations;

		//Current animation
		AnimationClip* currentAnimationClip;
	};
}
