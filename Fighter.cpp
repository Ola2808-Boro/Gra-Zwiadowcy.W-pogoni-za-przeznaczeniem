#include "stdafx.h"
#include "Fighter.h"

Fighter::Fighter(float x, float y, Texture& texture_sheet)
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
	this->initInventory();




}
//--------------------------------------------------Destruktor--------------------------------------------------//
Fighter::~Fighter()
{
	delete this->inventory;
	delete this->weapon;
}
//--------------------------------------------Funkcje--------------------------------------------------------//
void Fighter::initVariables()
{
	this->initAttack = false;
	this->attacking = false;
	this->weapon = new Sword(1, 2, 5, 60, 20, "Resources/Images/sprite/sword.png");//value
	//unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, string texture_file
	this->weapon->generate(1, 3);//const unsigned levelMax, const unsigned levelMin
	this->damageTimerMax = 500;
}

void Fighter::initComponents()//sprawdzic
{

	this->movementComponent = NULL;
	this->animationcomponent = NULL;
}

void Fighter::initAnimation()//sprawdz czy jest w konstruktorze
{
	this->animationcomponent->addAnimation("IDLE", 5.f, 0, 0, 1, 0, 64, 64);
	this->animationcomponent->addAnimation("WALK_UP", 5.f, 0, 1, 5 ,1, 64, 64);
	this->animationcomponent->addAnimation("WALK_LEFT", 5.f,0 ,2 , 5, 2, 64, 64);
	this->animationcomponent->addAnimation("WALK_DOWN", 5.f,2,0 ,5 , 0, 64, 64);
	this->animationcomponent->addAnimation("WALK_RIGHT", 5.f,0 ,2 , 5, 0, 64, 64);
	//this->animationcomponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 33);
}

void Fighter::initInventory()
{
	this->inventory = new Inventory(100);
}

void Fighter::update(const float& dt, Vector2f& mouse_pos_view, const View& view)//dopasowuje tekstury do kierunku ruchu(juz to jest w initAnimation)
{

	this->movementComponent->update(dt);
	this->updateAnimation(dt);
	this->hitboxcomponent->update();
	this->weapon->update(mouse_pos_view, sf::Vector2f(this->getSpriteCenter().x, this->getSpriteCenter().y + 5.f));

}

void Fighter::render(RenderTarget& target, const bool show_hitbox)
{
	
	target.draw(this->sprite);
	this->weapon->render(target);


	if (show_hitbox)
		this->hitboxcomponent->render(target);


}



void Fighter::updateAnimation(const float& dt)//do niej przesniose rzeczy z update a w update zrobie wywolanie tej funkcji
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

void Fighter::loseHp(const int hp)
{
	this->attributeComponent->loseHp(hp);
}

void Fighter::gainHp(const int hp)
{
	this->attributeComponent->gainHp(hp);
}

void Fighter::loseExp(const int exp)
{
	this->attributeComponent->loseExp(exp);
}

void Fighter::gainExp(const int exp)
{
	this->attributeComponent->gainExp(exp);
}

void Fighter::setInitAttack(const bool initAttack)
{
	this->initAttack = initAttack;
}

AttributeComponent* Fighter::getAttributeComponent()
{
	return this->attributeComponent;
}

Weapon* Fighter::getWeapon() const
{
	return this->weapon;
}

const string Fighter::toStringCharacterTab() const
{
	stringstream sss;
	const AttributeComponent* ac = this->attributeComponent;
	const Weapon* w = this->weapon;
	sss << "Level: " << ac->level << "\n"
		<< "Exp: " << ac->exp << "\n"
		<< "Exp next: " << ac->expNext << "\n"
		<< "Weapon Level: " << w->getLevel() << "\n"
		<< "Weapon Type: " << w->getType() << "\n"
		<< "Weapon Value: " << w->getValue() << "\n"
		<< "Weapon Range: " << w->getRange() << "\n"
		<< "Weapon Damage Min: " << w->getDamageMin() + this->attributeComponent->damageMin << " (" << this->attributeComponent->damageMin << ")" << "\n"
		<< "Weapon Damage Max: " << w->getDamageMax() + this->attributeComponent->damageMax << " (" << this->attributeComponent->damageMax << ")" << "\n";

	return sss.str();
}

const bool& Fighter::getInitAttack() const
{
	return this->initAttack;
}

const bool Fighter::getDamageTimer()
{
	if (this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax)
	{
		this->damageTimer.restart();
		return true;
	}

	return false;
}

const unsigned Fighter::getDamage() const
{
	return rand() % (
		(this->attributeComponent->damageMax + this->weapon->getDamageMax())
		- (this->attributeComponent->damageMin + this->weapon->getDamageMin()) + 1)
		+ (this->attributeComponent->damageMin + this->weapon->getDamageMin());
}