#include "stdafx.h"
#include "HelpState.h"

HelpState::HelpState(VideoMode& vm, Font& font) :font(font)
{

	this->background.setSize(Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
	background.setFillColor(Color(20, 20, 20, 100));
	//conatinerem ustawiam wymiary tego okna
	this->container.setSize(Vector2f(static_cast<float>((vm.width) / 2.f), static_cast<float>(vm.height)/*-gui::p2pY(9.3f,vm)*/));
	container.setFillColor(Color(20, 20, 20));
	container.setPosition(static_cast<float>(vm.width / 2.f - this->container.getSize().x / 2.f), 0.f);


	this->helpText.setFont(font);
	this->helpText.setFillColor(Color(255, 255, 255));
	this->helpText.setCharacterSize(gui::calucuateCharacterSize(vm));//sprawdzone  dla bledy calculateCharacterSize
	this->helpText.setString("HELP");
	this->helpText.setPosition(Vector2f((container.getPosition().x + this->container.getSize().x / 2.f - this->helpText.getGlobalBounds().width / 2.f), (container.getPosition().y + gui::p2pY(4.f, vm))));


	this->helpTextInfo.setFont(font);
	this->helpTextInfo.setFillColor(Color(204, 102, 0));
	this->helpTextInfo.setCharacterSize(gui::calucuateCharacterSize(vm));//sprawdzone  dla bledy calculateCharacterSize
	this->helpTextInfo.setString
	("W-UP\n D-RIGHT \n S-DOWN\n A-LEFT\n LEFT MOSUE BUTTON-ATTACK\n C-INFORMATION ABOUT THE HERO\n ");
	this->helpTextInfo.setPosition(Vector2f((container.getPosition().x +250 - this->helpText.getGlobalBounds().width / 2.f), (container.getPosition().y + 300)));

}
//--------------------------------------------------------Destruktor------------------------------------------//
HelpState::~HelpState()//usuwa wszytsko z kontenera
{
	auto it = this->buttons.begin();
	for (auto it = this->buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

map<string, gui::Button*>& HelpState::getButtons()
{
	return this->buttons;
}


//Funckje
void HelpState::update(Vector2i& mousePostWindow)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePostWindow);

	}
}

void HelpState::render(RenderTarget& target)
{
	target.draw(background);
	target.draw(container);
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}


	target.draw(helpText);
	target.draw(helpTextInfo);



}

void HelpState::addButtons(string key, float y, const float width, const float height, const unsigned char_size, string text)
{

	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;
	//x = this->container.getPosition().x + container.getSize().x/3.f;//dopasowac pod rozmiar
	//y = this->container.getPosition().y + container.getSize().y / 4.f;//dopasowac pod rozmiar
	this->buttons[key] = new gui::Button(x, y, width, height, text, this->font, Color(217, 146, 24, 85), Color::Cyan, Color::Yellow, Color(240, 101, 14, 94), Color::Red, Color::Yellow, 20, Color::Red, Color(235, 44, 19, 92), Color(235, 44, 19, 92));
	//float x, float y, float width, float height, string text_button, Font font_button, Color hoverColor, Color activeColor, Color idleColor, Color outlinehoverColor, Color outlineidleColor,
	//Color outlineactiveColor, unsigned character_size, Color text_idle, Color text_hover, Color text_active, short unsigned id
}

const bool& HelpState::isButtonPressed(const string key)
{
	return this->buttons[key]->isPressed();
}

