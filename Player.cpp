#include "Player.h"

void Player::initVariables()
{
	this->movementComponent = NULL;
	this->animationcomponent = NULL;
}

void Player::initComponents()
{
	this->attacking = false;
}

void Player::update(const float &dt)//dopasowuje tekstury do kierunku ruchu 
{
	
	movementComponent->update(dt);
	/*if (Mouse::isButtonPressed(Mouse::Left))
	{
		attacking = true;
	}*/
	if (attacking)
	{
		this->animationcomponent->play("Attack", dt, true);//ustawiam priority na true,ale ttack nie dziala
	}
	if (movementComponent->getStates(Idle))//zwroci prawde jak bedzie stal w miejscu
	{
		this->animationcomponent->play("Idle_left", dt);//rusza sie w miejscu
	}
	else if(movementComponent->getStates(MovingRight))
	{
		
		sprite.setOrigin(258.f, 0.f);//za co bede go lapac
		sprite.setScale(-1.f, 1.f);//odbija go, dlatego potrzebuje tylko jednego walka
		this->animationcomponent->play("Walk_left", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());//rusza sie w miejscu
	}
	else if (movementComponent->getStates(MowingLeft))
	{
		
		sprite.setOrigin(0.f, 0.f);//za co bede go lapac
		sprite.setScale(1.f, 1.f);
		this->animationcomponent->play("Walk_left", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());//rusza sie w miejscu
	}
	else if (movementComponent->getStates(MowingUp))
	{
		
		this->animationcomponent->play("Walk_left", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());//rusza sie w miejscu
	}
	else if (movementComponent->getStates(MovingDown))
	{
	
		this->animationcomponent->play("Walk_left", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());//rusza sie w miejscu
	}
	hitboxcomponent->update();
	
}

Player::Player(float x ,float y ,Texture &texture_sheet)
{
	this->initVariables();
	this->initComponents();
	this->setPosition(x, y);//ustawienie
	this->createMovementComponent(300.f, 1500.f, 1000.f);;//przykladowa max predkosc
	this->createAnimationComponent(texture_sheet);
	this->createHitboxComponent(sprite,86,74,86,111);
	this->animationcomponent->addAnimation("Idle_left", 11.f, 0, 0, 13, 0, 192, 192);
	this->animationcomponent->addAnimation("Walk_left", 6.f, 0, 1, 11, 1, 192, 192);
	this->animationcomponent->addAnimation("Attack", 5.f, 0, 2, 13, 2, 192*2, 192);;//jeszcze nie dziala
}

Player::~Player()
{
}
