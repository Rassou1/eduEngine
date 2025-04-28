#pragma once

class AnimationComponent
{
	AnimationComponent();

public:
	
	int animationIndex;
	float animationSpeed;

	AnimationComponent(int animationIndex, float animationSpeed)
	{
		this->animationIndex = animationIndex;
		this->animationSpeed = animationSpeed;
	}
};