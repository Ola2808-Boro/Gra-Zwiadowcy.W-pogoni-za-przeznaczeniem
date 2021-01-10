#include "stdafx.h"
#include "AttributeComponent.h"
//-----------------------------KONSTRUKTOR----------------------------------------//
AttributeComponent::AttributeComponent(int level)
{
	this->level = level;;
	this->exp=0;
	this->expNext = (50 * pow(this->level, 3) - 150 * pow(this->level, 2) + (UINT64)400 * this->level) / 3;
	this->attributePoints=2;

	this->vitality = 1;
	this->strength = 1;
	this->dexterity = 1;
	this->agility = 1;
	this->intelligence = 1;

	this->updateLevel();
	this->updateStats(true);
}
//----------------------------------DESTRUKTOR----------------------------------------//
AttributeComponent::~AttributeComponent()
{
}
string AttributeComponent::debugPrint() const
{
	stringstream sss;
	sss << "Level" << this->level <<" "<<"Exp:"<<" "<<this->exp<<" "<<"ExpNex:"<<" "<<this->expNext<<"AttributePoints"<<" "<<this->attributePoints<< endl;
	return sss.str();
}
//----------------------------FUNKCJE----------------------------------------------//
void AttributeComponent::updateStats(const bool reset)
{
	this->hpMax = this->vitality * 5 + this->vitality + this->strength / 2 + this->intelligence / 5;
	this->damageMin = this->strength * 2 + this->strength / 4 + this->intelligence / 5;
	this->damageMax = this->strength * 2 + this->strength / 2 + this->intelligence / 5;
	this->accuracy = this->dexterity * 5 + this->dexterity / 2 + this->intelligence / 5;
	this->defence = this->agility * 2 + this->agility / 4 + this->intelligence / 5;
	this->luck = this->intelligence * 2 + this->intelligence / 5;
	if (reset)
	{
		this->hp = this->hpMax;
	}
}


void AttributeComponent::updateLevel()
{
	while (this->exp>=this->expNext)//dopoki to obecne exp jest wieksze rowne temu nastpnemu, to zwieksze level
	{
		level++;
		this->exp -= this->expNext;
		this->expNext = (50 * pow(this->level, 3) - 150 * pow(this->level, 2) + (UINT64)400 * this->level) / 3;;
		this->attributePoints++;
	
	}
}

void AttributeComponent::update()
{
	this->updateLevel();	
}

void AttributeComponent::gainExp(const int exp)
{
	this->exp += exp;
	this->updateLevel();
}

void AttributeComponent::loseHp(const int hp)
{
	this->hp -= hp;
	if (this->hp < 0)
	{
		this->hp = 0;
		
		
	}
}

void AttributeComponent::gainHp(const int hp)
{
	this->hp += hp;
	if ((this->hp) > (this->hpMax))
	{
		this->hp = this->hpMax;
	}
}

void AttributeComponent::loseExp(const int exp)
{
	this->exp -= exp;
	if (this->exp < 0)
	{
		this->exp = 0;
	}
}

void AttributeComponent::render(RenderTarget& target)
{
	
}

const bool AttributeComponent::isDead() const
{
	return this->hp<=0;
}
