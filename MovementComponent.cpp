#include"stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(Sprite& sprite,float maxVelocity, float acceleration, float deceleration): sprite(sprite),maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{

}

MovementComponent::~MovementComponent()
{
}

const Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

void MovementComponent::move(const float direction_x, const float direction_y, const float& dt)
{
	/* Accelerating a sprite until it reaches the max velocity. */
	cout << direction_x << " " << direction_y << endl;
	this->velocity.x += this->acceleration * direction_x * dt;
	this->velocity.y += this->acceleration * direction_y * dt;
	cout << velocity.x << " " << velocity.y << endl;
	
}

void MovementComponent::stopVelocity()
{
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX()//ma ustawic velocity na 0
{
	this->velocity.x = 0.f;
	
}
void MovementComponent::stopVelocityY()//ma ustawic velocity na 0
{

	this->velocity.y = 0.f;
}

const bool MovementComponent::getStates(unsigned state) const
{
	switch (state)
	{
	case Idle:
	{
		if (velocity.x == 0 && velocity.y == 0)//czyli kiedy on stoi w miejscu
		{
			return true;
		}
		break;
	}
	case Moving:
	{
		if (velocity.x != 0 || velocity.y != 0)//czyli kiedy sie rusza, ale obojetnie czy w lewo czy w prawo
		{
			return true;
		}
		break;
	}
	case MovingDown:
	{
		if (velocity.y < 0)//czyli kiedy sie rusza w lewo
		{
			return true;
		}
		break;
	}
	case MovingRight:
	{
		if (velocity.x > 0)//czyli kiedy sie rusza w prawo
		{
			return true;
		}
		break;
	}
	case MowingLeft:
	{
		if (velocity.x < 0)//czyli kiedy sie rusza w lewo
		{
			return true;
		}
		break;
	}
	case MowingUp:
	{
		if (velocity.y > 0)//czyli kiedy sie rusza w lewo
		{
			return true;
		}
		break;
	}
	default:
		break;
	}
	return false;
}

const bool& MovementComponent::getMaxVelocity() const
{
	return maxVelocity;
}

void MovementComponent::update(const float& dt)
{
	
	/*
	Decelerates the sprite and controls the maximum velocity.
	Moves the sprite.
	*/

	if (this->velocity.x > 0.f) //Check for positive x
	{
		//Max velocity check
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		//Deceleration
		this->velocity.x -= deceleration * dt;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f) //Check for negative x
	{
		//Max velocity check
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		//Deceleration
		this->velocity.x += deceleration * dt;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	if (this->velocity.y > 0.f) //Check for positive y
	{
		//Max velocity check
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		//Deceleration
		this->velocity.y -= deceleration * dt;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f) //Check for negative y
	{
		//Max velocity check
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		//Deceleration
		this->velocity.y += deceleration * dt;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	//Final move
	this->sprite.move(dt*velocity); //Uses velocity
}
