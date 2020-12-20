#include "stdafx.h"
#include "PlayerGui.h"


PlayerGui::PlayerGui(Player* player, VideoMode& vm):vm(vm)
{
	this->player = player;
	this->initFont();
	this->initLevelElement();
	this->initExpBar();
	this->initHPBar();
}

PlayerGui::~PlayerGui()
{
	delete this->hpBar;
	delete this->expBar;
}

void PlayerGui::initFont()
{
	this->font.loadFromFile("Fonts/FjallaOne-Regular.ttf");
}

void PlayerGui::initHPBar()
{
	this->hpBar = new gui::ProgressBar(1.f, 8.3f, 10.4f, 2.8f,this->player->getAttributeComponent()->hpMax,Color::Red,180,&this->font, this->vm );

	//zastapione przez klase stworzona w Gui
	/*float width = gui::p2pX(10.4f, this->vm);
	float height = gui::p2pY(1.8f, this->vm);
	float x = gui::p2pX(1.f, this->vm);
	float y = gui::p2pY(8.3f, this->vm);
	this->hpBarMaxSizeWidth = width;
	this->hpBarText.setFont(font);
	this->hpBarText.setCharacterSize(gui::calucuateCharacterSize(this->vm, 150));

	this->hpBarBack.setSize(Vector2f(width, height));
	this->hpBarBack.setFillColor(Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(x, y);

	this->hpBarInner.setSize(Vector2f(width, height));
	this->hpBarInner.setFillColor(Color(250, 20, 20, 200));
	this->hpBarInner.setPosition(this->hpBarBack.getPosition());

	this->hpBarText.setPosition(this->hpBarInner.getPosition().x + 10.f, this->hpBarInner.getPosition().y + 5.f);*/
}

void PlayerGui::initExpBar()//bedzie nizej niz hp
{

	this->expBar = new gui::ProgressBar(1.f, 5.6f, 10.4f, 1.9f, this->player->getAttributeComponent()->exp,Color::Blue,220, &this->font, this->vm);

	/*float width = gui::p2pX(10.4f, this->vm);
	float height = gui::p2pY(1.9f, this->vm);
	float x = gui::p2pX(1.f, this->vm);
	float y = gui::p2pY(5.6f, this->vm);
	this->expBarMaxSizeWidth = width;

	this->expBarText.setFont(font);
	this->expBarText.setCharacterSize(gui::calucuateCharacterSize(this->vm, 200));

	this->expBarBack.setSize(Vector2f(width, height));
	this->expBarBack.setFillColor(Color(50, 50, 50, 200));
	this->expBarBack.setPosition(x, y);

	this->expBarInner.setSize(Vector2f(width, height));
	this->expBarInner.setFillColor(Color(20, 250, 20, 200));
	this->expBarInner.setPosition(this->expBarBack.getPosition());

	this->expBarText.setPosition(this->expBarInner.getPosition().x + this->levelElementBack.getPosition().x + gui::p2pX(0.53f, this->vm), this->expBarInner.getPosition().y + this->levelElementBack.getPosition().x + gui::p2pY(0.15f, this->vm));*/
}

void PlayerGui::initLevelElement()
{
	float width = gui::p2pX(1.6f, this->vm);
	float height = gui::p2pY(2.8f, this->vm);
	float x = gui::p2pX(1.f, this->vm);
	float y = gui::p2pY(1.9f, this->vm);

	this->levelElementBack.setSize(sf::Vector2f(width, height));
	this->levelElementBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->levelElementBack.setPosition(x, y);

	this->levelElementText.setFont(this->font);
	this->levelElementText.setCharacterSize(gui::calucuateCharacterSize(this->vm, 150));
	this->levelElementText.setPosition(this->levelElementBack.getPosition().x + gui::p2pX(0.53f, this->vm), this->levelElementBack.getPosition().y + gui::p2pY(0.5f, this->vm));
}


void PlayerGui::update(const float& dt)
{
	this->updateLevelElement();
	this->updateHPBar();
	this->updateExpBar();
}

void PlayerGui::render(RenderTarget& target)
{
	this->renderLevelElement(target);
	this->renderHPBar(target);
	this->renderExpBar(target);
}

void PlayerGui::renderHPBar(RenderTarget& target)
{
	this->hpBar->renderProgressBar(target);

}

void PlayerGui::renderExpBar(RenderTarget& target)
{
	this->expBar->renderProgressBar(target);
}

void PlayerGui::renderLevelElement(RenderTarget& target)
{
	target.draw(levelElementBack);
	target.draw(levelElementText);
}

void PlayerGui::updateHPBar()
{
	this->hpBar->updateProgressBar(this->player->getAttributeComponent()->hp);//(const int current_value), to bedzie moja biezaca wartosc dla klasy w Gui
}

void PlayerGui::updateLevelElement()
{
	this->levelElementString = to_string(this->player->getAttributeComponent()->level);
	this->levelElementText.setString(this->levelElementString);
}

void PlayerGui::updateExpBar()
{
	this->expBar->updateProgressBar(this->player->getAttributeComponent()->exp);
}
