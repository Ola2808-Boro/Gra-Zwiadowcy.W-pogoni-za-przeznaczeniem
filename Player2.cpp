#include "stdafx.h"
#include "Player2.h"

//--------------------------------------Konstruktor------------------------------------------------------//
Player2::Player2(float x, float y, Texture& texture_sheet)
{
	//4 funkcje inicjalizujace
	this->initVariables();
	this->initComponents();//sprawdzic?

	this->createHitboxComponent(this->sprite, 86.f, 81.f, 86.f, 111.f);
	this->createMovementComponent(140.f, 1400.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->creatAttributeComponent(1);//mam ta funkcje w klasie o tej nazwie
	this->creatSkillComponent();
	this->setPosition(x, y);//ustawienie
	this->initAnimation();





}
//--------------------------------------------------Destruktor--------------------------------------------------//
Player2::~Player2()
{

}
//--------------------------------------------Funkcje--------------------------------------------------------//
void Player2::initVariables()
{
	this->initAttack = false;
	this->attacking = false;
	//unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, string texture_file
	this->damageTimerMax = 500;
}

void Player2::initComponents()//sprawdzic
{

	this->movementComponent = NULL;
	this->animationcomponent = NULL;
}

void Player2::initAnimation()//sprawdz czy jest w konstruktorze
{
	this->animationcomponent->addAnimation("Idle", 10.f, 0, 0, 13, 0, 192, 192);
	this->animationcomponent->addAnimation("Walk", 10.f,0, 1, 11, 1, 192, 192);
	//this->animationcomponent->addAnimation("Walk_Left", 11.f, 4, 1, 7, 1, 192, 192);
	/*this->animationcomponent->addAnimation("Attack", 7.f, 0, 2, 13, 2, 192*2, 192 * 2);*/
}



void Player2::update(const float& dt, Vector2f& mouse_pos_view, const View& view)//dopasowuje tekstury do kierunku ruchu(juz to jest w initAnimation)
{

	this->movementComponent->update(dt);
	this->updateAnimation(dt);
	this->hitboxcomponent->update();
	

}

void Player2::render(RenderTarget& target, const bool show_hitbox)
{

	target.draw(this->sprite);
	


	if (show_hitbox)
		this->hitboxcomponent->render(target);


}



void Player2::updateAnimation(const float& dt)//do niej przesniose rzeczy z update a w update zrobie wywolanie tej funkcji
{
	if (this->attacking)
	{

	}


	if (movementComponent->getStates(Idle))//zwroci prawde jak bedzie stal w miejscu
	{
		this->animationcomponent->play("Idle", dt);//rusza sie w miejscu
	}
	else if (movementComponent->getStates(MovingRight))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			sprite.setOrigin(258.f, 0.f);//za co bede go lapac
			sprite.setScale(-1.f, 1.f);//odbija go, dlatego potrzebuje tylko jednego walk
		}
		this->animationcomponent->play("Walk", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());//rusza sie w miejscu
	}
	else if (movementComponent->getStates(MovingLeft))
	{

		if (this->sprite.getScale().x < 0.f)
		{
			sprite.setOrigin(0.f, 0.f);//za co bede go lapac
			sprite.setScale(1.f, 1.f);//odbija go, dlatego potrzebuje tylko jednego walk
		}
		this->animationcomponent->play("Walk", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());//rusza sie w miejscu
	}
	else if (movementComponent->getStates(MovingUp))
	{

		this->animationcomponent->play("Walk", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());//rusza sie w miejscu
	}
	else if (movementComponent->getStates(MovingDown))
	{

		this->animationcomponent->play("Walk", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());//rusza sie w miejscu
	}
}

void Player2::loseHp(const int hp)
{
	this->attributeComponent->loseHp(hp);
}

void Player2::gainHp(const int hp)
{
	this->attributeComponent->gainHp(hp);
}

void Player2::loseExp(const int exp)
{
	this->attributeComponent->loseExp(exp);
}

void Player2::gainExp(const int exp)
{
	this->attributeComponent->gainExp(exp);
}

void Player2::setInitAttack(const bool initAttack)
{
	this->initAttack = initAttack;
}

AttributeComponent* Player2::getAttributeComponent()
{
	return this->attributeComponent;
}
const bool& Player2::getInitAttack() const
{
	return this->initAttack;
}

const bool Player2::getDamageTimer()
{
	if (this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax)
	{
		this->damageTimer.restart();
		return true;
	}

	return false;
}
const bool Player2::isDead() const
{
	if (this->attributeComponent)
	{
		return this->attributeComponent->isDead();//funkcja w AttributeComponent, ktora sprawdza, czy hp worga jest rowne, ponizje 0
	}
	else
	{
		return false;
	}
}
