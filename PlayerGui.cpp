#include "stdafx.h"
#include "PlayerGui.h"


PlayerGui::PlayerGui(Player* player)
{
	this->player = player;
	this->initFont();
	this->initLevelElement();
	this->initExpBar();
	this->initHPBar();
}

PlayerGui::~PlayerGui()
{
}

void PlayerGui::initFont()
{
	this->font.loadFromFile("Fonts/FjallaOne-Regular.ttf");
}

void PlayerGui::initHPBar()
{
	float width =300.f ;
	this->hpBarMaxSizeWidth = width;
	float height = 50.f;
	float x = 20.f;
	float y = 20.f;
	this->hpBarText.setFont(font);
	this->hpBarText.setCharacterSize(16);

	this->hpBarBack.setSize(Vector2f(width, height));
	this->hpBarBack.setFillColor(Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(x, y);

	this->hpBarInner.setSize(Vector2f(width, height));
	this->hpBarInner.setFillColor(Color(250, 20, 20, 200));
	this->hpBarInner.setPosition(this->hpBarBack.getPosition());

	this->hpBarText.setPosition(this->hpBarInner.getPosition().x + 10.f, this->hpBarInner.getPosition().y + 5.f);
}

void PlayerGui::initExpBar()//bedzie nizej niz hp
{
	float width = 200.f;
	this->expBarMaxSizeWidth = width;
	float height = 50.f;
	float x = 20.f;
	float y = 80.f;
	this->expBarText.setFont(font);
	this->expBarText.setCharacterSize(14);

	this->expBarBack.setSize(Vector2f(width, height));
	this->expBarBack.setFillColor(Color(50, 50, 50, 200));
	this->expBarBack.setPosition(x, y);

	this->expBarInner.setSize(Vector2f(width, height));
	this->expBarInner.setFillColor(Color(20, 250, 20, 200));
	this->expBarInner.setPosition(this->expBarBack.getPosition());

	this->expBarText.setPosition(this->expBarInner.getPosition().x + 10.f, this->expBarInner.getPosition().y + 5.f);
}

void PlayerGui::initLevelElement()
{
	float width = 50.f;
	float height = 40.f;
	float x = 20.f;
	float y = 20.f;

	this->levelElementText.setFont(font);
	this->levelElementText.setCharacterSize(18);

	this->levelElementBack.setSize(Vector2f(width, height));
	this->levelElementBack.setFillColor(Color(50, 50, 50, 200));
	this->levelElementBack.setPosition(x, y);

	this->levelElementText.setPosition(this->levelElementBack.getPosition().x + 10.f, this->levelElementBack.getPosition().y + 5.f);
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
	target.draw(hpBarBack);
	target.draw(hpBarInner);
	target.draw(hpBarText);

}

void PlayerGui::renderExpBar(RenderTarget& target)
{
	target.draw(expBarBack);
	target.draw(expBarInner);
	target.draw(expBarText);
}

void PlayerGui::renderLevelElement(RenderTarget& target)
{
	target.draw(levelElementBack);
	target.draw(levelElementText);
}

void PlayerGui::updateHPBar()
{
	//dzielenie hp na hpmax
	float percent =static_cast<float>(this->player->getAttributeComponent()->hp) / static_cast<float>(this->player->getAttributeComponent()->hpMax);
	this->hpBarInner.setSize(Vector2f(static_cast<float>(floor(this->hpBarMaxSizeWidth*percent)),this->hpBarInner.getSize().y));
	this->hpBarString = to_string(this->player->getAttributeComponent()->hp)+" / "+to_string(this->player->getAttributeComponent()->hpMax);
	this->hpBarText.setString(this->hpBarString);
}

void PlayerGui::updateLevelElement()
{
	this->levelElementString = to_string(this->player->getAttributeComponent()->level);
	this->levelElementText.setString(this->levelElementString);
}

void PlayerGui::updateExpBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->exp) / static_cast<float>(this->player->getAttributeComponent()->expNext);
	this->expBarInner.setSize(Vector2f(static_cast<float>(floor(this->expBarMaxSizeWidth * percent)), this->expBarInner.getSize().y));
	this->expBarString = to_string(this->player->getAttributeComponent()->exp) + " / " + to_string(this->player->getAttributeComponent()->expNext);
	this->expBarText.setString(this->expBarString);
}
