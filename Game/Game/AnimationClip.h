#pragma once

#include <iostream>
#include <string>

#include <SFML\Graphics.hpp>

//Include upper hierachy class Component because it does inherit from the base class Component
#include "Component.h"

//Namespace Base Component
namespace BC {
	//Animation component class
	//Handles animation for a custom inserted sprite
	class AnimationClip : public Component {
	public:
		//Constructor
		AnimationClip(std::string animationName, std::string pathToSpritesheet, sf::Vector2u imageCount, int totalImages, float switchTime, sf::Sprite& spriteToAnimate, int oneRowCount);
		//Destructor
		~AnimationClip();

		//Override Start method from base Component class
		void Start();
		//Override Update method from base Component class
		void Update(float deltaTime);

		//Play animation method
		void Play();
		//Stop animation method
		void Stop();

		//Returns the switchTime float
		float GetSwitchTime();
		//Returns the name of the animation
		std::string GetName();

		//To set animation playing state
		bool isPlaying;
	private:
		//Name of animation
		std::string animationName;

		//Time in total of a the animation running
		float totalTime;
		//Total time before a new frame is selected
		float switchTime;

		//Local frame rect
		sf::IntRect intRect;
		//Local texture loaded from spritesheet
		sf::Texture texture;

		//Local total images
		int totalImages;
		//Local current images counted
		int localImagesCount;
		//Vector that holds the vertical and horizontal images
		sf::Vector2u imageCount;
		//Coordinates of current set image in spritesheet
		sf::Vector2u currentImageCoordinates;

		//Sprite to animate the animation in
		sf::Sprite& spriteToAnimate;

		//To set if to animate in one row
		int oneRowCount;

		
	};
}

