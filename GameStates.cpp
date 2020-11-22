#include"stdafx.h"
#include "GameStates.h"

void GameStates::initKeybinds()
{
	ifstream ifs("Config/gamestate_keybinds.ini");
	if (ifs.is_open())
	{
		string key = "";
		string key2 = "";

		while (ifs >> key >> key2)//dopoki pobiera te dwie wartosci
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
	
		}

	}
	ifs.clear();
	ifs.seekg(0);//beginning
	ifs.close();
	
}

void GameStates::initTextures()
{
	
	this->temp.loadFromFile("Resources/Images/sprite/PLAYER_SHEET.png");
	this->textures["Player_1"] =&temp;
}
void GameStates::InitFonts()
{
	if (!this->font.loadFromFile("Fonts/FjallaOne-Regular.ttf"))
	{
		throw("Error::Could not load font");
	}
}

void GameStates::initPauseMenu()
{
	this->pauseMenu = new PausedMenu(*this->window, this->font);
	this->pauseMenu->addButtons("Quit", 100.f, 100.f, "Quit");
}

void GameStates::initPlayers()
{
	//this->player = new Player(0, 0, this->textures["Player_1"]);
	this->player = new Player(0, 0, *this->textures["Player_1"]);
}



GameStates::GameStates(RenderWindow* window,GraphicsSettings gfxSettings, map <string, int>* supportedKeys, stack <State*>* states) :State(window, gfxSettings, supportedKeys, states)
{
	this->initKeybinds();
	this->initTextures();
	this->initPlayers();
	this->InitFonts();
	this->initPauseMenu();
}

GameStates::~GameStates()
{
	delete this->player;
	delete this->pauseMenu;
}

void GameStates::update(const float& dt)
{
	this->updateMousePosition();
	this->updateKeyTime(dt);
	this->updateInput(dt);
	
	if (!paused)//jezeli nie ma pauzy to ciagle aktualizuj
	{
	
		this->updatePlayerInput(dt);
		this->player->update(dt);
	}
	else
	{
		
		this->pauseMenu->update(this->mousePostView);
		this->updatePauseMenuButtons();
		
	}

}


void GameStates::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	cout << "Render map w GS" << endl;
	this->tilemap.render(*target);
	this->player->render(*target);
	if (this->paused)
	{
		this->pauseMenu->render(*target);
	}
	
}

void GameStates::updatePlayerInput(const float& dt)//sprawdzoen,dziala
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Left"))))
	{
		cout << keybinds.at("Move_Left") << endl;
		this->player->move(-1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Move_Right"))))
	{
		cout << "Powinno byc 3,a jest"<<" "<<keybinds.at("Move_Right") << endl;
		this->player->move(1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Move_Up"))))
	{
		cout << "Powinno byc 22,a jest" << " " << keybinds.at("Move_Up") << endl;
		this->player->move(0.f, -1.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Move_Down"))))
	{
		cout << "Powinno byc 18,a jest" << " " << keybinds.at("Move_Down") << endl;
		this->player->move(0.f, 1.f, dt);
	}
	

}

void GameStates::updateInput(const float dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Escape) && this->getKeyTime())//jak bedziesz miala czas do zmien na keybinds itp.
	{
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpauseState();
		}
	}
}

void GameStates::updatePauseMenuButtons()
{
	if (pauseMenu->isButtonPressed("Quit"))
	{
		this->endState();
	}
}


