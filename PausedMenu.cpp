#include"stdafx.h"
#include "PausedMenu.h"

PausedMenu::PausedMenu(RenderWindow& window, Font& font):font(font)
{
	
	this->background.setSize(Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
	background.setFillColor(Color(20, 20, 20, 100));
	//conatinerem ustawiam wymiary tego okna
	this->container.setSize(Vector2f(static_cast<float>((window.getSize().x)/2.f), static_cast<float>((window.getSize().y))));
	container.setFillColor(Color(20, 20, 20));
	container.setPosition(static_cast<float>(window.getSize().x/2.f-this->container.getSize().x/2.f),0.f);

	this->menuText.setFont(font);
	this->menuText.setFillColor(Color(255, 255, 255));
	this->menuText.setCharacterSize(60);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(Vector2f((container.getPosition().x+this->container.getSize().x/2.f-this->menuText.getGlobalBounds().width/2.f), (container.getPosition().y+20.f)));

}

PausedMenu::~PausedMenu()//usuwa wszytsko z kontenera
{
	auto it = this->buttons.begin();
	for (auto it = this->buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

map<string, gui::Button*>& PausedMenu::getButtons()
{
	return this->buttons;
}


//Funckje
void PausedMenu::update(Vector2f mousePos)
{
	for (auto & i :this->buttons)
	{
		i.second->update(mousePos);

	}
}

void PausedMenu::render(RenderTarget& target)
{
	target.draw(background);
	target.draw(container);
	for (auto &i:this->buttons)
	{
		i.second->render(target);
	}
	target.draw(menuText);
}

void PausedMenu::addButtons(string key,float x,float y, string text)
{
	float width = 250.f;
	x = this->container.getPosition().x + container.getSize().x/3.f;//dopasowac pod rozmiar
	y = this->container.getPosition().y + container.getSize().y / 4.f;//dopasowac pod rozmiar
	this->buttons[key] = new gui::Button(x, y, 150, 50, text, this->font, Color::Blue, Color::Cyan, Color::Yellow, Color::Black,Color::Red,Color::Yellow, 20, Color::Red, Color::Yellow, Color::White, 0);
}

const bool& PausedMenu::isButtonPressed(const string key) 
{
	return this->buttons[key]->isPressed();
}
