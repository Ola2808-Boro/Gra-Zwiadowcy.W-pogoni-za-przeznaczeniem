#include "stdafx.h"
#include "GameOverState.h"

GameOverState::GameOverState(VideoMode& vm, Font& font) :font(font)
{
	cout << "Jestem w konsruktorze" << endl;
	this->background.setSize(Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
	background.setFillColor(Color(20, 20, 20, 100));
	//conatinerem ustawiam wymiary tego okna
	this->container.setSize(Vector2f(static_cast<float>((vm.width) / 2.f), static_cast<float>(vm.height)/*-gui::p2pY(9.3f,vm)*/));
	container.setFillColor(Color(20, 20, 20));
	container.setPosition(static_cast<float>(vm.width / 2.f - this->container.getSize().x / 2.f), 0.f);

	this->gameOverText.setFont(font);
	this->gameOverText.setFillColor(Color::Red);
	this->gameOverText.setCharacterSize(100);
	this->gameOverText.setString("GAME OVER");
	this->gameOverText.setPosition(900 - (gameOverText.getGlobalBounds().width / 2.f),400 - (gameOverText.getGlobalBounds().height / 2.f));
	



}
//--------------------------------------------------------Destruktor------------------------------------------//
GameOverState::~GameOverState()//usuwa wszytsko z kontenera
{
	auto it = this->buttons.begin();
	for (auto it = this->buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

map<string, gui::Button*>& GameOverState::getButtons()
{
	return this->buttons;
}


//Funckje
void GameOverState::update(Vector2i& mousePostWindow)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePostWindow);

	}
}

void GameOverState::render(RenderTarget& target)
{
	target.draw(background);
	target.draw(container);
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
	target.draw(gameOverText);

}

void GameOverState::addButtons(string key, float y, const float width, const float height, const unsigned char_size, string text)
{

	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;
	this->buttons[key] = new gui::Button(x, y, width, height, text, this->font, Color(217, 146, 24, 85), Color::Cyan, Color::Yellow, Color(240, 101, 14, 94), Color::Red, Color::Yellow, 20, Color::Red, Color(235, 44, 19, 92), Color(235, 44, 19, 92));
}

const bool& GameOverState::isButtonPressed(const string key)
{
	return this->buttons[key]->isPressed();
}
