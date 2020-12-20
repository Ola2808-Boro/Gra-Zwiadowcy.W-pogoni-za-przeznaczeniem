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
	
	this->temp.loadFromFile("Resources/Images/sprite/PLAYER_SHEET2.png");
	this->textures["Player_1"] =temp;
	if (!this->textures["RAT1_SHEET"].loadFromFile("Resources/Images/sprite/rat1_60x64.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_RAT1_TEXTURE";
	}

	if (!this->textures["BIRD1_SHEET"].loadFromFile("Resources/Images/sprite/bird1_61x57.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
	}
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
	const VideoMode& vm = this->stateData->gfxSettings->resolutions;
	//sprawdzone pod wzgledem id i dla bledy calculateCharacterSize
	this->pauseMenu = new PausedMenu(this->stateData->gfxSettings->resolutions, this->font);
	this->pauseMenu->addButtons("Quit", gui::p2pY(74.f, vm),gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calucuateCharacterSize(vm),"Quit");
	/*this->pauseMenu->addButtons("Save", 250.f, 800.f,100.f,50.f, "Save");*/
}

void GameStates::initTileMap()
{
	//this->tileMap = new TileMap(this->stateData->gridSize, 100, 100,"Resources/Images/tile/tilesheet1.png" );//sprawdzic, czy ze zmiana dziala bylo 10 10
	this->tileMap=new TileMap("text.ini");// zmienic nazwe funkcji na loadFromFile
}

void GameStates::initPlayerGui()
{
	/*Player* player, VideoMode& vm*/
	this->playerGui = new PlayerGui(this->player,this->stateData->gfxSettings->resolutions);//sprawdzic czy jest w konstruktorze i destruktorze
}

void GameStates::initShaders()
{
	if (!this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER." << "\n";
	}
}

void GameStates::initPlayers()
{
	//this->player = new Player(0, 0, this->textures["Player_1"]);
	this->player = new Player(220, 220, this->textures["Player_1"]);
}



GameStates::GameStates(StateData* stateData):State(stateData)
{
	this->iniDefferedRender();
	this->initView();
	this->initKeybinds();
	this->InitFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initShaders();
	this->initPlayers();
	this->initPlayerGui();
	this->initTileMap();	

	this->activeEnemies.push_back(new Enemy(200.f, 100.f, this->textures["RAT1_SHEET"]));

	
}

GameStates::~GameStates()
{
	delete this->pauseMenu;
	delete this->player;
	delete this->playerGui;
	delete this->tileMap;
	for (size_t i = 0; i <this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}
}

void GameStates::updateView(const float& dt)
{
	
	this->view.setSize(Vector2f(static_cast<float>(stateData->gfxSettings->resolutions.width), static_cast<float>(stateData->gfxSettings->resolutions.height)));
	this->view.setCenter(
		floor(this->player->getPosition().x + (static_cast<float>(this->mousePostWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolutions.width / 2)) / 10.f),
		floor(this->player->getPosition().y + (static_cast<float>(this->mousePostWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolutions.height / 2)) / 10.f)
	);
	if (this->tileMap->getMaxSizeF().x>=this->view.getSize().x )
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
		{
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
		else if (this->view.getCenter().x - this->view.getSize().x / 2.f > this->tileMap->getMaxSizeF().x)
		{
			this->view.setCenter(this->tileMap->getMaxSizeF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}
	if (this->tileMap->getMaxSizeF().y>=this->view.getSize().y )
	{
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
		{
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
		}
		else if (this->view.getCenter().y + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeF().y)
		{
			this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeF().y - this->view.getSize().y / 2.f);
		}
	}


	this->mousePosGrid.x =static_cast<int>( this->view.getCenter().x )/ static_cast<int>(this->stateData->gridSize);
	this->mousePosGrid.y =static_cast<int>( this->view.getCenter().y )/ static_cast<int>(this->stateData->gridSize);
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
		this->player->update(dt,this->mousePostView);
		this->playerGui->update(dt);
		for (auto *i :this->activeEnemies)
		{
			i->update(dt, this->mousePostView);
		}
		
	}
	else
	{
		
		this->pauseMenu->update(this->mousePostWindow);
		this->updatePauseMenuButtons();
		
	}

}

void GameStates::updateTileMap(const float& dt)//sprawdzic
{
	this->tileMap->update(this->player,dt);
	for (auto* i : this->activeEnemies)
	{
		this->tileMap->update(i, dt);
	}

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
	this->tileMap->render(this->renderTexture,this->viewGridPosition,&this->core_shader,this->player->getCenter(),false);
	/*this->enemy->render(this->renderTexture, &this->core_shader, this->player->getCenter(), true);*/
	this->player->render(this->renderTexture, &this->core_shader, this->player->getCenter(), true);
	this->tileMap->renderDeferred(this->renderTexture, &this->core_shader, this->player->getCenter());
	for (auto* i : this->activeEnemies)
	{
		i->render(this->renderTexture, &this->core_shader, this->player->getCenter(), false);
	}
	renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGui->render(this->renderTexture);
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




