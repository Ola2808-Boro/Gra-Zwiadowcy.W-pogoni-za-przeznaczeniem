#include "stdafx.h"
#include "PlayerGuiTabs.h"

//------------------------------Konstruktor----------------------------------------------------//
PlayerGuiTabs::PlayerGuiTabs(VideoMode& vm, Font& font, Player& player): vm(vm), font(font), player(player)
{
	this->initKeyTime();
	this->initTab();
}
//------------------------------Destruktor----------------------------------------------------//
PlayerGuiTabs::~PlayerGuiTabs()
{

}
//----------------------------------Funkcje--------------------------------------------------//
void PlayerGuiTabs::update()
{
	for (size_t i = 0; i < this->tabs.size(); i++)
	{
		if (this->tabs[i]->getOpen())
		{
			this->tabs[i]->update();
		}
	}
}

void PlayerGuiTabs::render(RenderTarget& target)
{
	for (size_t i = 0; i < this->tabs.size(); i++)
	{
		if (this->tabs[i]->getOpen())

		{
			this->tabs[i]->render(target);
		}
	}
}

void PlayerGuiTabs::initTab()
{
	this->tabs.push_back(new CharacterTabs(vm, font, player));
}

void PlayerGuiTabs::initKeyTime()
{
	this->keyTimeMax = 0.3f;
	this->keyTimer.restart();
}

void PlayerGuiTabs::toggleTab(const int tab_index)
{
	if (tab_index>0|| tab_index< this->tabs.size())
	{
		this->tabs[tab_index]->toggle();
	}
	
}

const bool PlayerGuiTabs::getKeyTime()
{
	if (this->keyTimer.getElapsedTime().asSeconds()  >= this->keyTimeMax)
	{
		this->keyTimer.restart();
		return true;
	}
	return false;
}

const bool PlayerGuiTabs::tapsOpen()
{
	bool open = false;
	for (size_t i = 0; i < this->tabs.size() && !open; i++)
	{
		if (this->tabs[i]->getOpen())
		{
			open = true;
		}
	}

	return open;
}
