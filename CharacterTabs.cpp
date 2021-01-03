#include "stdafx.h"
#include "CharacterTabs.h"
//poprawic Ola pamietaj
CharacterTabs::CharacterTabs(VideoMode& vm, Font& font, Player& player):Tabs(vm, font,  player, false)
{
	//tlo
	this->CharacterTabsBackground.setFillColor(Color(230, 230, 230));
	this->CharacterTabsBackground.setSize(Vector2f(gui::p2pX(30.f, this->vm), static_cast<float>(this->vm.height)));

	this->initText();
}


CharacterTabs::~CharacterTabs()
{
}

void CharacterTabs::initText()
{
	//tekst
	this->characterTabsInfoText.setFont(font);
	this->characterTabsInfoText.setCharacterSize(gui::calucuateCharacterSize(this->vm, 60));
	this->characterTabsInfoText.setFillColor(Color::White);
	this->characterTabsInfoText.setPosition(this->CharacterTabsBackground.getPosition().x + 20.f, this->CharacterTabsBackground.getPosition().y + 20.f);
	
	this->characterTabsInfoText.setString(this->player.toStringCharacterTab());
}

void CharacterTabs::update()
{
	if (!this->hidden)//jezeli nie jest ukryty
	{
		this->characterTabsInfoText.setString(this->player.toStringCharacterTab());
	}
}

void CharacterTabs::render(RenderTarget& target)
{
	if (!this->hidden)//jezeli nie jest ukryty
	{
		target.draw(CharacterTabsBackground);
		target.draw(characterTabsInfoText);
	}
	
}
