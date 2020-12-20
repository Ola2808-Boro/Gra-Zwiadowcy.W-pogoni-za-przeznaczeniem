#include"stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->hitboxcomponent = NULL;
	this->animationcomponent = NULL;
	this->movementComponent = NULL;
	this->attributeComponent = NULL;
	this->skillComponent = NULL;
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
	delete this->attributeComponent;
	delete this->skillComponent;
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
	this->animationcomponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createHitboxComponent(Sprite& sprite, float offset_x, float offset_y, float width, float height)
{
	this->hitboxcomponent = new HitboxComponent(this->sprite,offset_x,offset_y,width,height);
}

void Entity::creatAttributeComponent(const int level)
{
	this->attributeComponent = new AttributeComponent(level);//sprawdz czy usuwasz pozniej
}

void Entity::creatSkillComponent()
{
	this->skillComponent = new SkillComponent();
}

const FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxcomponent)
	{
		return this->hitboxcomponent->getGlobalBounds();;
	}
	return this->sprite.getGlobalBounds();
}

const Vector2f& Entity::getPosition() const
{
	if (hitboxcomponent)
	{
		return this->hitboxcomponent->getPosition();
	}
	return this->sprite.getPosition();

}

const Vector2i Entity::getGridPosition(const int GridSizeI) const
{
	if (this->hitboxcomponent)
	{
		return Vector2i(static_cast<int>(this->hitboxcomponent->getPosition().x / GridSizeI), static_cast<int>(this->hitboxcomponent->getPosition().y / GridSizeI));
	}
	else
	{
		return Vector2i(static_cast<int>(this->sprite.getPosition().x / GridSizeI), static_cast<int>(this->sprite.getPosition().y / GridSizeI));

	}
}

void Entity::setPosition(const float x, const float y)
{
	if (hitboxcomponent)
	{
		this->hitboxcomponent->setPosition(x, y);
	}
	else
	{
		this->sprite.setPosition(x, y);
	}

}

const FloatRect Entity::getNextPositionBounds(const float& dt) const
{
	if (this->hitboxcomponent && this->movementComponent)
		return this->hitboxcomponent->getNextPosition(this->movementComponent->getVelocity() * dt);

	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

const Vector2f Entity::getCenter() const
{
	if (this->hitboxcomponent)
	{
		return this->hitboxcomponent->getPosition() + Vector2f(this->hitboxcomponent->getGlobalBounds().width / 2.f, this->hitboxcomponent->getGlobalBounds().height / 2.f);
	}

	return this->sprite.getPosition() +Vector2f(this->sprite.getGlobalBounds().width / 2.f,this->sprite.getGlobalBounds().height / 2.f);
}

void Entity::stopVelocity()
{
	if (this->movementComponent)//jezeli itnieje
	{
		this->movementComponent->stopVelocity();
	}
}

void Entity::stopVelocityX()
{
	if (this->movementComponent)//jezeli itnieje
	{
		this->movementComponent->stopVelocityX();
	}
}

void Entity::stopVelocityY()
{
	if (this->movementComponent)//jezeli itnieje
	{
		this->movementComponent->stopVelocityY();
	}
}

void Entity::move(const float direction_x, const float  direction_y, const float& dt )
{
	if (this->movementComponent)//jezeli itnieje
	{
		//cout << "Istnieje" << endl;
		this->movementComponent->move(direction_x, direction_y,dt);
		
	}
	if (this->skillComponent)
	{
		this->skillComponent->gainExp(SKILLS::Endurance , 1);
		
	}
	
}


