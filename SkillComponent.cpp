#include "stdafx.h"
#include "SkillComponent.h"

SkillComponent::SkillComponent()
{
	
	this->skills.push_back(Skill(SKILLS::Health));// int type, wyliacznie w SkillComponent.h
	this->skills.push_back(Skill(SKILLS::Attack));// int type, wyliacznie w SkillComponent.h
	this->skills.push_back(Skill(SKILLS::Accuracy));// int type, wyliacznie w SkillComponent.h
	this->skills.push_back(Skill(SKILLS::Defence));// int type, wyliacznie w SkillComponent.h
	this->skills.push_back(Skill(SKILLS::Melee));// int type, wyliacznie w SkillComponent.h
	this->skills.push_back(Skill(SKILLS::Woodcutting));// int type, wyliacznie w SkillComponent.h
	this->skills.push_back(Skill(SKILLS::Mining));// int type, wyliacznie w SkillComponent.h
	this->skills.push_back(Skill(SKILLS::Hiperattack));// int type, wyliacznie w SkillComponent.h
	this->skills.push_back(Skill(SKILLS::Endurance));// int type, wyliacznie w SkillComponent.h
}

SkillComponent::~SkillComponent()
{
}

const int SkillComponent::getSkill(const int skill)const
{
	if (skills.empty() || skill < 0 || skill >= this->skills.size())

	{
		throw("ERROR::SKILLCOMPONENT::GETSKILL::SKILL DOES NOT EXIST: " + skill);
	}
	else
	{
		return this->skills[skill].getLevel();
	}
}

const int SkillComponent::gainExp(const int skill, const int exp)
{
	if (skills.empty() || skill < 0 || skill >= this->skills.size())

	{
		throw("ERROR::SKILLCOMPONENT::GETSKILL::SKILL DOES NOT EXIST: " + skill);
	}
	else
	{

		this->skills[skill].gainExp(exp);
	}
}
