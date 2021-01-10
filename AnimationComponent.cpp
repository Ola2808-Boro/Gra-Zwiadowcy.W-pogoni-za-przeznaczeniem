#include"stdafx.h"
#include "AnimationComponent.h"

//-----------------------------KONSTRUKTOR------------------------------------//
AnimationComponent::AnimationComponent(Sprite &sprite,Texture& texture_sheet):sprite(sprite), textureSheet(texture_sheet),lastAnimation(NULL), priorityanimation(NULL)
{

}
//-------------------------------DESTRUKTOR------------------------------//
AnimationComponent::~AnimationComponent()
{
		for (auto& i : this->animation)
		{
			delete i.second;
		}
	
	
}
AnimationComponent::Animation::~Animation()
{

}
//---------------------------FUNKCJE---------------------------------//

const bool& AnimationComponent::isDone(string key) 
{
	return this->animation[key]->isDone();
}

const bool& AnimationComponent::play(const string key,const float& dt,const bool priority)
{

	if (this->priorityanimation) //If there is a priority animation
	{
		cout << "jest protirty" << endl;
		if (this->priorityanimation == this->animation[key])
		{
			if (this->lastAnimation != this->animation[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animation[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animation[key];
				}
			}

			//If the priority animation is done, remove it
			if (this->animation[key]->play(dt))
			{
				this->priorityanimation = NULL;
			}
		}
	}
	else //Play animation of no other priority animation is set
	{
		//If this is a priority animation, set it.
		if (priority)
		{
			this->priorityanimation = this->animation[key];
		}

		if (this->lastAnimation != this->animation[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animation[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animation[key];
			}
		}

		this->animation[key]->play(dt);
	}

	return this->animation[key]->isDone();
	
}
const bool& AnimationComponent::play(const string key, const float& dt,const float& modifier, const float& modifier_max, const bool priority )
{
	if (this->priorityanimation) //If there is a priority animation
	{
		if (this->priorityanimation == this->animation[key])
		{
			if (this->lastAnimation != this->animation[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animation[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animation[key];
				}
			}

			//If the priority animation is done, remove it
			if (this->animation[key]->play(dt, abs(modifier / modifier_max)))
			{
				this->priorityanimation = NULL;
			}
		}
	}
	else //Play animation of no other priority animation is set
	{
		//If this is a priority animation, set it.
		if (priority)
		{
			this->priorityanimation = this->animation[key];
		}

		if (this->lastAnimation != this->animation[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animation[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animation[key];
			}
		}

		this->animation[key]->play(dt, abs(modifier / modifier_max));
	}

	return this->animation[key]->isDone();
}

void AnimationComponent::addAnimation(const string key,float animation_timer, int start_frame_x, int start_frame_y, int end_frame_x, int end_frame_y, int width, int height)
{
	this->animation[key] = new Animation(sprite, textureSheet, animation_timer, start_frame_x, start_frame_y, end_frame_x, end_frame_y, width, height);
}

