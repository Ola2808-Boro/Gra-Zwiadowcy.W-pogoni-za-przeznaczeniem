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

void GameStates::initPlayers()
{
	//this->player = new Player(0, 0, this->textures["Player_1"]);
	this->player = new Player(0, 0, *this->textures["Player_1"]);
}



GameStates::GameStates(RenderWindow* window, map <string, int>* supportedKeys, stack <State*>* states):State(window,supportedKeys,states)
{
	this->initKeybinds();
	this->initTextures();
	this->initPlayers();
}

GameStates::~GameStates()
{
	delete this->player;
}

void GameStates::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->player->update(dt);

}


void GameStates::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	this->player->render(*target);
	
}

void GameStates::updateInput(const float& dt)//sprawdzoen,dziala
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
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		this->endState();
	}

	//if (Keyboard::isKeyPressed(Keyboard::A))
	//{
	//	this->player->move(-1.f, 0.f, dt);
	//}
	//if (Keyboard::isKeyPressed(Keyboard::D))
	//{
	//	
	//	this->player->move(1.f, 0.f, dt);
	//}
	//if (Keyboard::isKeyPressed(Keyboard::W))
	//{
	//	
	//	this->player->move(0.f, -1.f, dt);
	//}
	//if (Keyboard::isKeyPressed(Keyboard::S))
	//{
	//	
	//	this->player->move(0.f, 1.f, dt);
	//}
	//if (Keyboard::isKeyPressed(Keyboard::Escape))
	//{
	//	this->endState();
	//}
}



