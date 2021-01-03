#include"stdafx.h"
#include "PausedMenu.h"

//----------------------------------------------Konstruktor--------------------------------------------------//
PausedMenu::PausedMenu(VideoMode& vm, Font& font):font(font)
{
	
	this->background.setSize(Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
	background.setFillColor(Color(20, 20, 20, 100));
	//conatinerem ustawiam wymiary tego okna
	this->container.setSize(Vector2f(static_cast<float>((vm.width)/2.f), static_cast<float>(vm.height)/*-gui::p2pY(9.3f,vm)*/));
	container.setFillColor(Color(20, 20, 20));
	container.setPosition(static_cast<float>(vm.width /2.f-this->container.getSize().x/2.f),0.f);

	this->menuText.setFont(font);
	this->menuText.setFillColor(Color(255, 255, 255));
	this->menuText.setCharacterSize(gui::calucuateCharacterSize(vm));//sprawdzone  dla bledy calculateCharacterSize
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(Vector2f((container.getPosition().x+this->container.getSize().x/2.f-this->menuText.getGlobalBounds().width/2.f), (container.getPosition().y+gui::p2pY(4.f,vm))));

}
//--------------------------------------------------------Destruktor------------------------------------------//
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
void PausedMenu::update(Vector2i& mousePostWindow)
{
	for (auto & i :this->buttons)
	{
		i.second->update(mousePostWindow);

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

void PausedMenu::addButtons(string key,float y,const float width,const float height,const unsigned char_size, string text)
{
	
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;
	//x = this->container.getPosition().x + container.getSize().x/3.f;//dopasowac pod rozmiar
	//y = this->container.getPosition().y + container.getSize().y / 4.f;//dopasowac pod rozmiar
	this->buttons[key] = new gui::Button(x, y, width, height, text, this->font, Color::Blue, Color::Cyan, Color::Yellow, Color::Black,Color::Red,Color::Yellow, 20, Color::Red, Color::Yellow, Color::White);
}

const bool& PausedMenu::isButtonPressed(const string key) 
{
	return this->buttons[key]->isPressed();
}
