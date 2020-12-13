#include"stdafx.h"
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
	this->updateAttack();
	this->updateAnimation(dt);
	hitboxcomponent->update();
	
}

void Player::render(RenderTarget& target)
{

	this->hitboxcomponent->render(target);
	
}

void Player::updateAnimation(const float& dt)//do niej przesniose rzeczy z update a w update zrobie wywolanie tej funkcji
{
	if (this->animationcomponent->play("Attack", dt, true));//ustawiam priority na true,ale Attack nie dziala,spojrz na AnimationComponent
	{//Ustawiam setOrigin(moj punkt zaczepienia)w zaleznosci do tego w jaka strone bedzie zwrocony
		this->attacking = false;//ustawiam z powrotem)
		if (this->sprite.getScale().x > 0.f)//jezeli jest zwrocony w lewo(x narastaja )
		{
			sprite.setOrigin(96.f, 0.f);//za co bede go lapac
		}
		else//jezeli jest zwrocony w prawo
		{
			sprite.setOrigin(258.f+96.f, 0.f);//za co bede go lapac
		}

		if (this->animationcomponent->play("Attack", dt, true))
		{
			attacking= false;
			sprite.setOrigin(9.f, 0.f);
		}
		else//jezeli jest zwrocony w prawo
		{
			sprite.setOrigin(258.f, 0.f);//za co bede go lapac
		}
	

	}
	if (movementComponent->getStates(Idle))//zwroci prawde jak bedzie stal w miejscu
	{
		this->animationcomponent->play("Idle_left", dt);//rusza sie w miejscu
	}
	else if (movementComponent->getStates(MovingRight))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			sprite.setOrigin(258.f, 0.f);//za co bede go lapac
			sprite.setScale(-1.f, 1.f);//odbija go, dlatego potrzebuje tylko jednego walk
		}
		this->animationcomponent->play("Walk_left", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());//rusza sie w miejscu
	}
	else if (movementComponent->getStates(MowingLeft))
	{

		if (this->sprite.getScale().x < 0.f)
		{
			sprite.setOrigin(0.f, 0.f);//za co bede go lapac
			sprite.setScale(1.f, 1.f);//odbija go, dlatego potrzebuje tylko jednego walk
		}
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
}

void Player::updateAttack()//do tej funckji z update przenioslam rzeczy dotyczace ataku
{
	if (Mouse::isButtonPressed(Mouse::Right))
	{
		attacking = true;
	}
}

void Player::loseHp(const int hp)
{
	this->attributeComponent->hp -= hp;
	if (this->attributeComponent->hp< 0)
	{
		attributeComponent->hp = 0;
	}
}

void Player::gainHp(const int hp)
{
	this->attributeComponent->hp += hp;
	if ((this->attributeComponent->hp)>(this->attributeComponent->hpMax))
	{
		attributeComponent->hp = this->attributeComponent->hpMax;
	}
}

void Player::loseExp(const int exp)
{
	this->attributeComponent->exp -= exp;
	if (this->attributeComponent->exp < 0)
	{
		attributeComponent->exp = 0;
	}
}

void Player::gainExp(const int exp)
{
	this->attributeComponent->gainExp(exp);
}

Player::Player(float x ,float y ,Texture &texture_sheet)
{
	this->initVariables();
	this->initComponents();
	this->setPosition(x, y);//ustawienie
	this->createMovementComponent(300.f, 1500.f, 1000.f);;//przykladowa max predkosc
	this->createHitboxComponent(sprite, 86.f, 74.f, 86.f, 111.f);
	this->createAnimationComponent(texture_sheet);
	this->creatAttributeComponent(1);//mam ta funkcje w klasie o tej nazwie
	
	this->animationcomponent->addAnimation("Idle_left", 11.f, 0, 0, 13, 0, 192, 192);
	this->animationcomponent->addAnimation("Walk_left", 6.f, 0, 1, 11, 1, 192, 192);
	this->animationcomponent->addAnimation("Attack",    5.f, 0, 2, 13, 2, 384, 192);//jeszcze nie dziala,nadal nie mam pojecia 
	
}

Player::~Player()
{
}

AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}

