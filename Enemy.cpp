#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(/*EnemySpawner& enemy_Spawner,*/ float x, float y, Texture& texture_sheet)/*:enemySpawner(enemy_Spawner)*/
{
	
		this->initVariables();
		this->createMovementComponent(300.f, 1500.f, 1000.f);;//przykladowa max predkosc
		this->createHitboxComponent(this->sprite, 12.f, 10.f, 40.f, 54.f);
		this->createAnimationComponent(texture_sheet);

	
		this->setPosition(x, y);//ustawienie
		this->initAnimation();



	
}

Enemy::~Enemy()
{
}
void Enemy::initVariables()
{
	
}
void Enemy::initAnimation()//sprawdz czy jest w konstruktorze
{
	this->animationcomponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
	this->animationcomponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
	this->animationcomponent->addAnimation("WALK_LEFT", 11.f, 4, 1, 7, 1, 64, 64);
	this->animationcomponent->addAnimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 64);
	this->animationcomponent->addAnimation("WALK_UP", 11.f, 12, 1, 15, 1, 64, 64);
	this->animationcomponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 64);
}
void Enemy::update(const float& dt, Vector2f& mouse_pos_view)//dopasowuje tekstury do kierunku ruchu(juz to jest w initAnimation)
{

	this->movementComponent->update(dt);
	//this->updateAttack();
	this->updateAnimation(dt);
	this->hitboxcomponent->update();
	

}

void Enemy::render(RenderTarget& target, Shader* shader, const Vector2f light_position, const bool show_hitbox)
{
	if (shader)
	{

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		target.draw(this->sprite, shader);
		
	}
	else
	{
		target.draw(this->sprite);
	}
	if (show_hitbox)
	{
		this->hitboxcomponent->render(target);
	}


}
void Enemy::updateAnimation(const float& dt)//do niej przesniose rzeczy z update a w update zrobie wywolanie tej funkcji
{
	/*if (this->attacking)
	{

	}*/


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