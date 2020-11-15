#include "Entity.h"

void Entity::initVariables()
{
	this->hitboxcomponent = NULL;
	this->animationcomponent = NULL;
	this->movementComponent = NULL;
}

Entity::Entity()
{
	this->initVariables();
	
	
}

Entity::~Entity()
{
	delete this->movementComponent;
	delete this->animationcomponent;
	delete this->hitboxcomponent;
}

void Entity::setTexture(Texture& texture)
{
	
	this->sprite.setTexture(texture);
	//this->sprite->setTexture(*this->texture);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent( Texture& texture_sheet)
{
	this->animationcomponent = new AnimationComponent(sprite, texture_sheet);
}

void Entity::createHitboxComponent(Sprite& sprite, float offset_x, float offset_y, float width, float height)
{
	this->hitboxcomponent = new HitboxComponent(this->sprite,offset_x,offset_y,width,height);
}

void Entity::setPosition(const float x, const float y)
{
		this->sprite.setPosition(x , y);
	

}

void Entity::update(const float& dt)//na strzalki
{
	
}

void Entity::render(RenderTarget &target)
{
	
		target.draw(this->sprite);
		if (this->hitboxcomponent)//jezeli istnieje
		{
			hitboxcomponent->render(target);

		}
	
}

void Entity::move(const float direction_x, const float  direction_y, const float& dt )
{
	if (this->movementComponent)//jezeli itnieje
	{
		cout << "Istnieje" << endl;
		this->movementComponent->move(direction_x, direction_y,dt);
		
	}
}

