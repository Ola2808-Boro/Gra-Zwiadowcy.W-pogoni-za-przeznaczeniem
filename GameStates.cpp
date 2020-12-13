#include"stdafx.h"
#include "GameStates.h"

void GameStates::iniDefferedRender()
{
	this->renderTexture.create(this->stateData->gfxSettings->resolutions.width, this->stateData->gfxSettings->resolutions.height);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(IntRect(0, 0, this->stateData->gfxSettings->resolutions.width, this->stateData->gfxSettings->resolutions.height));
}

void GameStates::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolutions.width / 2),
			static_cast<float>(this->stateData->gfxSettings->resolutions.height / 2)
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolutions.width) / 2.f,
			static_cast<float>(this->stateData->gfxSettings->resolutions.height) / 2.f
		)
	);
}

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

void GameStates::initPauseMenu()//tyczy sie new game
{
	this->pauseMenu = new PausedMenu(*this->window, this->font);
	this->pauseMenu->addButtons("Quit", 250.f, 500.f,100.f,50.f, "Quit");
	/*this->pauseMenu->addButtons("Save", 250.f, 800.f,100.f,50.f, "Save");*/
}

void GameStates::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100,"Resources/Images/tile/tilesheet1.png" );//sprawdzic, czy ze zmiana dziala bylo 10 10
	this->tileMap->loadFromFile("text.txt");// zmienic nazwe funkcji na loadFromFile
}

void GameStates::initPlayerGui()
{
	this->playerGui = new PlayerGui(this->player);//sprawdzic czy jest w konstruktorze i destruktorze
}

void GameStates::initPlayers()
{
	//this->player = new Player(0, 0, this->textures["Player_1"]);
	this->player = new Player(0, 0, *this->textures["Player_1"]);
}



GameStates::GameStates(StateData* stateData):State(stateData)
{
	this->iniDefferedRender();
	this->initView();
	this->initKeybinds();
	this->InitFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
	this->initPlayerGui();
	this->initTileMap();
	
	
}

GameStates::~GameStates()
{
	delete this->pauseMenu;
	delete this->player;
	delete this->playerGui;
	delete this->tileMap;
}

void GameStates::updateView(const float& dt)
{
	this->view.setCenter(floor(this->player->getPosition().x), floor(this->player->getPosition().y));//powinno ustawic srodek kamery, tam gdzie bedzie nasz player,trzeba ta funkcje uwzglednic we wszytskich update jak jest niezatrzymany, floor zaokraglanie w dol
}

void GameStates::update(const float& dt)
{
	this->updateMousePosition(&this->view);
	this->updateKeyTime(dt);
	this->updateInput(dt);
	
	if (!paused)//jezeli nie ma pauzy to ciagle aktualizuj
	{
		this->updateView(dt);
		this->updatePlayerInput(dt);
		this->updateTileMap(dt);//musze sprawdzic kolizje przed ruszeniem postaci, koniecznie o tym pamietaj
		this->player->update(dt);
		this->playerGui->update(dt);
	}
	else
	{
		
		this->pauseMenu->update(this->mousePostWindow);
		this->updatePauseMenuButtons();
		
	}

}

void GameStates::updateTileMap(const float& dt)
{
	this->tileMap->update();
	this->tileMap->updateCollision(this->player,dt);
}


void GameStates::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	/*cout << "Render map w GS" << endl;*/
	this->renderTexture.clear();
	renderTexture.setView(this->view);
	this->tileMap->render(renderTexture,player->getGridPosition(static_cast<int>(this->stateData->gridSize)));
	this->player->render(renderTexture);
	this->tileMap->renderDeferred(this->renderTexture);
	renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGui->render(renderTexture);
	if (this->paused)
	{
		/*renderTexture.setView(this->renderTexture.getDefaultView());*/
		this->pauseMenu->render(renderTexture);
	}
	this->renderTexture.display();
	//this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(renderSprite);
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
		if (this->getKeyTime())
		{
			this->player->gainHp(1);
		}
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Move_Down"))))
	{
		cout << "Powinno byc 18,a jest" << " " << keybinds.at("Move_Down") << endl;
		this->player->move(0.f, 1.f, dt);
		if (this->getKeyTime())
		{
			this->player->loseHp(1);
		}
	}
	

}

void GameStates::updatePlayerGui(const float& dt)
{
	this->playerGui->update(dt);
}

void GameStates::updateInput(const float dt)
{
	if (sf::Keyboard::isKeyPressed(Keyboard::Escape)/*::Key(this->keybinds.at("Close")*/ && this->getKeyTime())//jak bedziesz miala czas do zmien na keybinds itp.
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



