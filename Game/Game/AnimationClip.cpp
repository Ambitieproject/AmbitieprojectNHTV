#include "AnimationClip.h"

using namespace BC;

//Constructor
AnimationClip::AnimationClip(std::string animationName, std::string pathToSpritesheet, sf::Vector2u imageCount, int totalImages, float switchTime, sf::Sprite& spriteToAnimate, int oneRowCount)
	: animationName(animationName), imageCount(imageCount), totalImages(totalImages), switchTime(switchTime), spriteToAnimate(spriteToAnimate), oneRowCount(oneRowCount) {
	//Load texture from a file path
	texture.loadFromFile(pathToSpritesheet);
	//Set width and height of rect
	intRect.width = texture.getSize().x / imageCount.x;
	intRect.height = texture.getSize().y / imageCount.y;
	//Set variables 
	totalTime = 0;
	localImagesCount = 0;
	currentImageCoordinates.x = 0;
	currentImageCoordinates.y = oneRowCount;

	isPlaying = false;

	//Set left and top of rect to be the same as the selected image multiplied by its width and height
	intRect.left = currentImageCoordinates.x * intRect.width;
	intRect.top = currentImageCoordinates.y * intRect.height;

	//Set the texture rect to the sprite its texture
	spriteToAnimate.setTextureRect(intRect);
}

//Destructor
AnimationClip::~AnimationClip() {

}

//Override Start method from base Component class
void AnimationClip::Start() {
	Component::Start();
}

//Override Update method from base Component class
void AnimationClip::Update(float deltaTime) {
	//If animation is on
	if (this->isPlaying) {
		Component::Update(deltaTime);
		//Increase totalTime by deltaTime
		totalTime += deltaTime;

		//if totalTime bigger then the switchTime
		if (totalTime >= switchTime) {
			//Reset total time
			totalTime = 0;
			//Increase count
			currentImageCoordinates.x++;
			localImagesCount++;

			//If local count of images is bigger or equal then the total images
			//Reset variables
			if (localImagesCount >= totalImages) {
				if (oneRowCount > 0) {
					currentImageCoordinates.y = oneRowCount;
				}
				else {
					currentImageCoordinates.y = 0;
				}

				currentImageCoordinates.x = 0;
				localImagesCount = 0;
			}
			//Else if x image is bigger then the total x images
			//Increase y value and set x value to 0
			else if (currentImageCoordinates.x >= imageCount.x) {
				currentImageCoordinates.y++;
				currentImageCoordinates.x = 0;
			}

			//Set left and top of rect to be the same as the selected image multiplied by its width and height
			intRect.left = currentImageCoordinates.x * intRect.width;
			intRect.top = currentImageCoordinates.y * intRect.height;

			//Set the texture rect to the sprite its texture
			spriteToAnimate.setTextureRect(intRect);
		}
	}
}

//Play animation method
void AnimationClip::Play() {
	isPlaying = true;
}

//Stop animation method
void AnimationClip::Stop() {
	isPlaying = false;
}

//Returns the switchTime float
float AnimationClip::GetSwitchTime() {
	return switchTime;
}

//Returns the name of the animation
std::string AnimationClip::GetName() {
	return animationName;
}
