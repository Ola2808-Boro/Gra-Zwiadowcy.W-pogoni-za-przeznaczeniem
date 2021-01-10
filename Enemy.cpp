#include "stdafx.h"
#include "Enemy.h"

//--------------------------------------Konstruktor------------------------------------------------------//
Enemy::Enemy(float x, float y, Texture& texture_sheet)
{
	//4 funkcje inicjalizujace
	this->initVariables();
	this->initComponents();//sprawdzic?

	this->createHitboxComponent(this->sprite, 16.f, 26.f, 32.f, 38.f);
	this->createMovementComponent(140.f, 1400.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->creatAttributeComponent(1);//mam ta funkcje w klasie o tej nazwie
	this->creatSkillComponent();
	this->setPosition(x, y);//ustawienie
	this->initAnimation();





}
//--------------------------------------------------Destruktor--------------------------------------------------//
Enemy::~Enemy()
{

}
//--------------------------------------------Funkcje--------------------------------------------------------//
void Enemy::initVariables()
{
	this->initAttack = false;
	this->attacking = false;
	this->damageTimerMax = 500;
	this->gainExp = 10;
}

void Enemy::initComponents()//sprawdzic
{

	this->movementComponent = NULL;
	this->animationcomponent = NULL;
}

void Enemy::initAnimation()//sprawdz czy jest w konstruktorze
{
	this->animationcomponent->addAnimation("IDLE", 15.f, 0, 10, 1, 10, 64, 64);
	this->animationcomponent->addAnimation("WALK_DOWN", 11.f, 0, 10, 8, 10, 64, 64);
	this->animationcomponent->addAnimation("WALK_LEFT", 11.f, 0, 9, 8, 9, 64, 64);
	this->animationcomponent->addAnimation("WALK_RIGHT", 11.f, 0, 11, 8, 11, 64, 64);
	this->animationcomponent->addAnimation("WALK_UP", 11.f, 0, 8, 8, 8, 64, 64);
	/*this->animationcomponent->addAnimation("Attack", 7.f, 0, 2, 13, 2, 192*2, 192 * 2);*/
}



void Enemy::update(const float& dt, Vector2f& mouse_pos_view, const View& view)//dopasowuje tekstury do kierunku ruchu(juz to jest w initAnimation)
{

	this->movementComponent->update(dt);
	this->updateAnimation(dt);
	this->hitboxcomponent->update();
	

}

void Enemy::render(RenderTarget& target, const bool show_hitbox)
{

	target.draw(this->sprite);
	


	if (show_hitbox)
		this->hitboxcomponent->render(target);


}



void Enemy::updateAnimation(const float& dt)//do niej przesniose rzeczy z update a w update zrobie wywolanie tej funkcji
{
	if (this->attacking)
	{

	}
	if (this->movementComponent->getStates(Idle))
	{
		this->animationcomponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getStates(MovingLeft))
	{
		this->animationcomponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getStates(MovingRight))
	{
		this->animationcomponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getStates(MovingUp))
	{
		this->animationcomponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getStates(MovingDown))
	{
		this->animationcomponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void Enemy::loseHp(const int hp)
{
	this->attributeComponent->loseHp(hp);
}

void Enemy::setInitAttack(const bool initAttack)
{
	this->initAttack = initAttack;
}

AttributeComponent* Enemy::getAttributeComponent()
{
	return this->attributeComponent;
}
const bool& Enemy::getInitAttack() const
{
	return this->initAttack;
}

const bool Enemy::getDamageTimer()
{
	if (this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax)
	{
		this->damageTimer.restart();
		return true;
	}

	return false;
}
const bool Enemy::isDead() const
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
const unsigned& Enemy::getGainExp() const
{
	return this->gainExp;
}
void Enemy::generateAttributes(const unsigned level)
{
	this->gainExp = level * (rand() % 5 + 1);
}